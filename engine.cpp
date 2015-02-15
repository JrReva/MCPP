#include "engine.h"
#include "cube.h"
#include <algorithm>
#include "menuitem.h"
#include "menupause.h"
#include "menuoptions.h"
#include "preferences.h"
#include "soundmanager.h"

Engine* Engine::m_instance = 0;

Engine* Engine::GetInstance() {
	return m_instance;
}

Engine::Engine() : m_showPicture(true), m_wireframe(false), m_showDebug(false), m_wPressed(false), m_aPressed(false), m_sPressed(false), m_dPressed(false), m_pause(false), m_pausePictureTaked(false), m_currentItemMenu(0), m_pixels(0)
{
	m_instance = this;
	
}

Engine::~Engine()
{
	delete m_currentItemMenu;
	delete MenuItem::GetInstance();
	delete MenuOptions::GetInstance();
	delete MenuPause::GetInstance();
	delete MenuCoeur::GetInstance();
	delete SoundManager::GetInstance();
	delete[] m_pixels;
	//delete m_mobHandler;
	delete Random::GetInstance();
}

void Engine::Init()
{
	
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		std::cerr << "Error while initializing glew .. abording (" << glewGetErrorString(err) << ")" << std::endl;
		abort();
	}

	glEnable(GL_CULL_FACE); // Cache les faces qui sont dos � nous

    glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
    glEnable(GL_TEXTURE_2D );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45.0f, (float)Width() / Height(), 0.1f, 1000.0f);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LINE_SMOOTH);

    // Light
    GLfloat light0Pos[4]  = {0.0f, CHUNK_SIZE_Y, 0.0f, 1.0f};
    GLfloat light0Amb[4]  = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat light0Diff[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light0Spec[4] = {0.2f, 0.2f, 0.2f, 1.0f};

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Spec);

    CenterMouse();
    HideCursor();

}

void Engine::DeInit()
{
}

void Engine::LoadResource()
{
    LoadTexture(m_textureCrosshair, TEXTURE_PATH "cross.bmp");
	
	SoundManager::GetInstance()->LoadRessources();
	SoundManager::GetInstance()->StartMusic();
	std::cout << "Loading and compiling shaders ..." << std::endl;

	BlockInfoEncapsuler::LoadRessources();
	m_blockInfos = BlockInfoEncapsuler::GetInstance();

	if (!m_shader01.Load(SHADER_PATH "shader01.vert", SHADER_PATH "shader01.frag", true))
	{
		std::cout << "Failed to load shader" << std::endl ;
		exit(1);
	}

	m_currentItemMenu = MenuCurrentItem::Instanciate(Width(), Height());
	m_currentItemMenu->Center(Width(), Height());
	
	m_menuCoeur = MenuCoeur::Instanciate(Width(), Height());
	m_menuCoeur->Center(Width(), Height());
	
	MenuItem* menuItem = MenuItem::Instanciate(Width(), Height());
	menuItem->Center(Width(), Height());

	MenuPause* menuPause = MenuPause::Instanciate(Width(), Height());
	menuPause->Center(Width(), Height());

	MenuOptions* menuOptions = MenuOptions::Instanciate(Width(), Height());
	menuOptions->Center(Width(), Height());

	//Generation du monde
	m_2dchunks.LoadResource();

	//Chargement des meshs et des textures à travers le MobFactory.
	//m_mobHandler = new MobHandler(&m_player);
}

void Engine::UnloadResource()
{
	m_2dchunks.SaveAll();
}

void Engine::Render(float elapsedTime)
{
	static float gameTime = elapsedTime;
	static float chunkEncapsulerRefresh = CHUNK_ENCAPSULER_CENTER_REFRESH;
    gameTime += elapsedTime;
	chunkEncapsulerRefresh -= elapsedTime;
	SoundManager::GetInstance()->Update(elapsedTime);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(Menu::GetCurrentMenu() != 0 && Menu::GetCurrentMenu()->IsPauseNeeded()) {
    	if(!m_pause)
    		SetPause(true);
    } else {
    	SetPause(false);
    }

    if(m_pause && m_pausePictureTaked) {
		if(m_showPicture) {
			glDrawPixels(Width(), Height(), GL_RGB, GL_UNSIGNED_BYTE,  m_pixels);
		}
		else{
			glClearColor(0.f, 0.f, 0.f, 1.f);
		}

		m_2dchunks.Render(elapsedTime, false);
		
		DrawHud(elapsedTime);

		return;
	}

    // Transformations initiales
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	// Simulate le deplacement du joueur pour vérifier s'il est dans un cube
	// et retourne la position actuel du joueur dans les temp
	if(GetFps() > 0)
	{
		m_player.MoveSimulation(elapsedTime);
		Collision(&m_player);

		if(chunkEncapsulerRefresh < 0) {
			chunkEncapsulerRefresh += CHUNK_ENCAPSULER_CENTER_REFRESH;
			m_2dchunks.SetPlayer2DPosition((int)m_player.Position().x, (int)m_player.Position().z);
		}
	}

	m_player.Render();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	m_shader01.Use();

	//Mise-à-jour des mobs.
	//m_mobHandler->Update(elapsedTime);

	//Determine which block type the player is in 
	Vector3f player_pos = m_player.GetCameraPosition();
	BlockType blockType = BlockAt(player_pos.x,player_pos.y,player_pos.z);
	GLfloat fogDensity = 0.f;

	if(blockType == BTYPE_AIR)
	{
		glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
		m_shader01.UpdateVec4Uniform("fogColor", 0.39f, 0.58f, 0.93f, 1.0f);
		fogDensity = Preferences::GetFogAirDensity();
	}
	else if(blockType == BTYPE_WATER)
	{
		glClearColor(0.f, 0.2f, 0.8f, 1.0f);
		m_shader01.UpdateVec4Uniform("fogColor", 0.f, 0.2f, 0.8f, 1.0f);
		fogDensity = Preferences::GetFogWaterDensity();
	}
	m_shader01.UpdateFloatUniform("fogDensity", fogDensity);

	BlockInfoEncapsuler::GetAtlas()->Bind();


	glTranslatef(.5f, .5f, .5f);
	m_2dchunks.Render(elapsedTime);
	 
	// Donne la position du bloc point� par le cursor
	GetBlocAtCursor();

	glDisable(GL_LIGHTING);
	Shader::Disable();

	DrawFaceColor();

	if(m_wireframe)
		glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
	DrawHud(elapsedTime);
	if(m_wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDisable(GL_BLEND);
}

void Engine::KeyPressEvent(unsigned char key)
{
    switch(key)
    {
	case 'w':
		if(!m_wPressed) {
			m_wPressed = true;
			m_player.SetMoveX(1);
		}
		break;
	case 'd':
		if(!m_dPressed) {
			m_dPressed = true;
			m_player.SetMoveY(-1);
		}
		break;
	case 's':
		if(!m_sPressed) {
			m_sPressed = true;
			m_player.SetMoveX(-1);
		}
		break;
	case 'a':
		if(!m_aPressed) {
			m_aPressed = true;
			m_player.SetMoveY(1);
		}
		break;
	case 2:		// Run (Shift)
		m_player.SetRun(true);
		break;
	case 21:	// Jump
		m_player.SetJump(true);
		break;
	case 102:		// fly (f)
		if(m_player.IsFlying() == false)
		SoundManager::GetInstance()->StartSound(SoundManager::FLY);
		m_player.SetFly(!m_player.IsFlying());
		break;
    }
}

void Engine::KeyReleaseEvent(unsigned char key)
{
    switch(key)
    {
    case 121:       // Y
        m_wireframe = !m_wireframe;
        if(m_wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
	case 'w':
		m_wPressed = false;

		if(!m_sPressed)
			m_player.SetMoveX(0);
		break;
	case 'd':
		m_dPressed = false;

		if(!m_aPressed)
			m_player.SetMoveY(0);
		break;
	case 's':
		m_sPressed = false;

		if(!m_wPressed)
			m_player.SetMoveX(0);
		break;
	case 'a':
		m_aPressed = false;

		if(!m_dPressed)
			m_player.SetMoveY(0);
		break;
	case 'i':
	case 'e':
		MenuItem::GetInstance()->Toggle();
		break;
	case 2:		// Shift
		m_player.SetRun(false);
		break;
	case 21:	// Jump
		m_player.SetJump(false);
		break;
	case 0:	    // ESC
		if(Menu::GetCurrentMenu() != 0) {
			Menu::GetCurrentMenu()->Hide();
		} else {
			MenuPause::GetInstance()->Show();
		}
        break;
    case 59:	// F11
        SetFullscreen(!IsFullscreen());
        break;
    case 58:	// F10
        m_showDebug = !m_showDebug;
        break;
    }

    if(key > 48 && key < 49 + NUMBER_CURRENT_ITEMS) {
    	int id = key - 49;
    	m_currentItemMenu->SetCurrentItem(id);
    }
}

void Engine::MouseMoveEvent(int x, int y)
{
	if(!m_haveFocus)
		return;

	m_currentItemMenu->MouseOver(x, Height() - y);
	if(Menu::GetCurrentMenu() != 0)
		Menu::GetCurrentMenu()->MouseOver(x, Height() - y);

	if(m_pause)
		return;

	// MakeRelativeToCenter exemple 
	// int x = 405 et le centre 400 le x devient 5 (400 - 405)
	MakeRelativeToCenter(x,y);
	m_player.TurnLeftRight((float)-x);
	m_player.TurnTopBottom((float)y);

    CenterMouse();
}

void Engine::MousePressEvent(const MOUSE_BUTTON &button, int x, int y)
{
	if(button == MOUSE_BUTTON_LEFT) {
		m_currentItemMenu->MouseClick(x, Height() - y);

		if(Menu::GetCurrentMenu() != 0)
			Menu::GetCurrentMenu()->MouseClick(x, Height() - y);
	}
}

void Engine::MouseWheelEvent(const MOUSE_BUTTON &button, int delta)
{
	int index = (m_currentItemMenu->GetCurrentItemIndex() - delta) % NUMBER_CURRENT_ITEMS;

	while(index < 0)
		index += NUMBER_CURRENT_ITEMS;
	
	m_currentItemMenu->SetCurrentItem(index);
}

void Engine::MouseReleaseEvent(const MOUSE_BUTTON &button, int x, int y)
{
	if(button == MOUSE_BUTTON_LEFT) {
		m_currentItemMenu->MouseClickReleased(x, Height() - y);

		if(Menu::GetCurrentMenu() != 0)
			Menu::GetCurrentMenu()->MouseClickReleased(x, Height() - y);
	}

	if(m_pause)
		return;

	//Si le x a la valeur ERROR_BLOCK_SELECTED, il n'y a aucun bloc selectionne
	if(m_currentBlock.x == ERROR_BLOCK_SELECTED)
			return;

	if(button == MOUSE_BUTTON_LEFT) // On enleve le block pointer
	{
		int cx, cz;

		// On recupere le chunk du bloc selectionne
		Chunk* c = m_2dchunks.GetChunkOfPoint(
				m_currentBlock.x,
				m_currentBlock.z, &cx, &cz);

		c->RemoveBloc(cx, m_currentBlock.y, cz);
	}
	else if (button == MOUSE_BUTTON_RIGHT) // On ajoute le block
	{
		//Calcule la nouvelle position du bloc
		Vector3i newBloc (
						m_currentBlock.x + m_currentFaceNormal.x,
						m_currentBlock.y + m_currentFaceNormal.y,
						m_currentBlock.z + m_currentFaceNormal.z
				);

		//TODO: Ajouter la vérification avec les mobs lorsqu'ils existeront
		if(m_player.GetCube().InCollisionWith(Cube((float)newBloc.x, (float)newBloc.y, (float)newBloc.z, (float)1, (float)1)))
			return;

		int cx, cz;

		//On recupere le chunk du nouveau bloc
		Chunk* c = m_2dchunks.GetChunkOfPoint(newBloc.x, newBloc.z, &cx, &cz);

		BlockType a = c->GetBloc(cx, newBloc.y, cz);
		//On ajoute le bloc
		if((*m_blockInfos)[a]->IsWalkable())
		{
			c->SetBloc(cx, newBloc.y, cz, GetBlocAjout());
		}
	}
}


bool Engine::LoadTexture(Texture& texture, const char* filename, bool stopOnError)
{
    texture.Load(filename);
    if(!texture.IsValid())
    {
        std::cerr << "Unable to load texture (" << filename << ")" << std::endl;
        if(stopOnError)
            Stop();

        return false;
    }

    return true;
}

// Affiche la Fps et la position du joueur � l'�cran et autres infos
void Engine::DrawHud(float elapsedTime)
{
	if(m_pause && !m_pausePictureTaked) {
		m_pixels = new unsigned char[3 * Width() * Height() + Width()];
		glReadPixels(0, 0, Width(), Height(), GL_RGB, GL_UNSIGNED_BYTE,  m_pixels);
		/*
		for(int i = 0; i < Width() * Height() * 3; ++i) {
			m_pixels[i] /= 3;
		}*/

		m_pausePictureTaked = true;
		m_showPicture = true;
	}

	static float counter = 0;
	counter += elapsedTime;

	// Setter le blend function , tout ce qui sera noir sera transparent
	glDisable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, Width() , 0, Height() , -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	// Affichage du crosshair
	m_textureCrosshair.Bind();
	static const int crossSize = 32;
	glLoadIdentity();
	glTranslated(Width() / 2 - crossSize / 2, Height() / 2 - crossSize / 2, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2i(0, 0);
	glTexCoord2f(1, 0);
	glVertex2i(crossSize, 0);
	glTexCoord2f(1, 1);
	glVertex2i(crossSize, crossSize);
	glTexCoord2f(0, 1);
	glVertex2i(0, crossSize);
	glEnd();

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	m_currentItemMenu->Draw();
	m_menuCoeur->Draw();

	if(Menu::GetCurrentMenu() != 0)
		Menu::GetCurrentMenu()->Draw();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	Menu::PrintText (20 , Height() - 25, 12, "MineCraft PlusPlus Beta");

	if(m_showDebug) {
		std::ostringstream ss;

		ss << "Fps : " << GetFps();
		Menu::PrintText (20 , Height() - 35, 12, ss.str());

		ss.str("") ;
		ss << "BlockType : " << (*m_blockInfos)[GetBlocAjout()]->GetName();
		Menu::PrintText (20 , Height() - 45, 12, ss.str());

		ss.str("") ;
		ss << "Position : " << m_player.Position();
		Menu::PrintText (20 , 10, 12, ss.str());

		ss.str("") ;
		ss << "Rotation : " << m_player.GetRotX() << ',' << m_player.GetRotY();
		Menu::PrintText (20 , 20, 12, ss.str());

		ss.str("") ;
		ss << "Face POINTE : " << m_currentFaceNormal;
		Menu::PrintText (20 , 30, 12, ss.str());

		ss.str("") ;
		ss << "Current Block : " << m_currentBlock;
		Menu::PrintText (20 , 40, 12, ss.str());

		ss.str("") ;
		ss << "Fly : " << m_player.IsFlying();
		Menu::PrintText (20 , 50, 12, ss.str());
	}
	
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

// Retourne le Fps
int Engine::GetFps()
{
	return OpenglContext::GetFps();
}


void Engine::Collision(MovableEntity* entity)
{
	Vector3f newPosition = entity->MoveAttempt();
	Cube actualCubePosition = entity->GetCube();
	Cube newCubePosition(newPosition.x, newPosition.y, newPosition.z, entity->Largeur(), entity->Hauteur());

	bool haveCollision = true;
	bool collideBottom = false;

	int startX, endX, startY, endY, startZ, endZ;

	int count = 0;
 
	endY = (int)floor(std::max(newCubePosition.y + newCubePosition.h, actualCubePosition.y + actualCubePosition.h));

	if(endY < CHUNK_SIZE_Y) {
		Cube testCube(0, 0, 0, 1, 1);
		while(haveCollision && count < 10) {
			haveCollision = false;

			startX = (int)floor(std::min(newCubePosition.x, actualCubePosition.x) + EPSILON);
			startY = (int)floor(std::min(newCubePosition.y, actualCubePosition.y) + EPSILON);
			startZ = (int)floor(std::min(newCubePosition.z, actualCubePosition.z) + EPSILON);
			
			endX = (int)floor(std::max(newCubePosition.x + newCubePosition.w, actualCubePosition.x + actualCubePosition.w) - EPSILON);
			endY = (int)floor(std::max(newCubePosition.y + newCubePosition.h, actualCubePosition.y + actualCubePosition.h) - EPSILON);
			endZ = (int)floor(std::max(newCubePosition.z + newCubePosition.w, actualCubePosition.z + actualCubePosition.w) - EPSILON);
		
			for(int x = startX; x <= endX && !haveCollision; ++x) {
				for(int y = startY; y <= endY && !haveCollision; ++y) {
					for(int z = startZ; z <= endZ && !haveCollision; ++z) {
							if(!(*m_blockInfos)[BlockAt(x, y, z)]->IsWalkable()) {
							haveCollision = true;
							++count;

							testCube.x = (float)x;
							testCube.y = (float)y;
							testCube.z = (float)z;

							CollisionPosition side = testCube.GetMaxPosition(actualCubePosition, newCubePosition);

							if(side == COLLISION_BOTTOM) {
								entity->SetOnGround(true);
								collideBottom = true;
							} else if(side == COLLISION_TOP) {
								entity->ResetVelocity();
							} else if(side == COLLISION_NONE) {
								haveCollision = false;
							}
						}
					}
				}
			}
		}
	
		if(!collideBottom && (*m_blockInfos)[BlockAt((int)floor(newCubePosition.x), (int)floor(newCubePosition.y - 1), (int)floor(newCubePosition.z))]->IsWalkable()) {
			entity->SetOnGround(false);
		}
	}
	
	entity->SetPosition(Vector3f(newCubePosition.x, newCubePosition.y, newCubePosition.z));
}

// Met en couleur le cot� du cube point�
void Engine::DrawFaceColor()
{
	int x = m_currentBlock.x;
	int y = m_currentBlock.y;
	int z = m_currentBlock.z;

	if(x != ERROR_BLOCK_SELECTED)
	{
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_POLYGON);
		   // front
		if(m_currentFaceNormal.z == 1)
		{
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x -.5f, y - .5f, z + .51f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x +.5f, y - .5f, z + .51f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x + .5f, y + .5f, z + .51f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x -.5f, y + .5f, z + .51f);
		}
		else if(m_currentFaceNormal.z == -1)
		{
		   // back
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x -.5f, y - .5f, z - .51f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x -.5f, y + .5f, z - .51f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x + .5f, y + .5f, z - .51f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x + .5f, y - .5f, z - .51f);
		}
		else if(m_currentFaceNormal.x == 1)
		{
		   // right
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x + .51f, y - .5f, z + .5f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x + .51f, y - .5f, z - .5f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x + .51f, y + .5f, z - .5f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x + .51f, y + .5f, z + .5f);
		}
		else if(m_currentFaceNormal.x == -1)
		{
		   // left
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x -.51f, y - .5f, z - .5f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x -.51f, y - .5f, z + .5f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x - .51f, y + .5f, z + .5f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x - .51f, y + .5f, z - .5f);

		}
		else if(m_currentFaceNormal.y == 1)
		{
		   // top
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x - .5f, y + .51f, z + .5f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x + .5f, y + .51f, z + .5f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x + .5f, y + .51f, z - .5f);
		   glColor4f(0,1,0,0.4);
		   glVertex3f(x - .5f, y + .51f, z - .5f);
		}
		else if(m_currentFaceNormal.y == -1)
		{
		   // bottom
		   glColor4f(0,1,0,0.4f);
		   glVertex3f(x + .5f, y - .51f, z + .5f);
		   glColor4f(0,1,0,0.4f);
		   glVertex3f(x - .5f, y - .51f, z + .5f);
		   glColor4f(0,1,0,0.4f);
		   glVertex3f(x - .5f, y - .51f, z - .5f);
		   glColor4f(0,1,0,0.4f);
		   glVertex3f(x + .5f, y - .51f, z - .5f);

		}
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}


}

void Engine::GetBlocAtCursor()
{
    int x = Width() / 2;
    int y = Height() / 2;

    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    posX += .5f;
    posY += .5f;
    posZ += .5f;

    // Le cast vers int marche juste pour les valeurs entiere, utiliser une fonction de la libc si besoin
    // de valeurs negatives
    int px = (int)floor(posX);
    int py = (int)floor(posY);
    int pz = (int)floor(posZ);



    bool found = false;

    if((m_player.GetCameraPosition() - Vector3f((float)posX, (float)posY, (float)posZ)).Length() < MAX_SELECTION_DISTANCE)
    {
        // Apres avoir determine la position du bloc en utilisant la partie entiere du hit
        // point retourne par opengl, on doit verifier de chaque cote du bloc trouve pour trouver
        // le vrai bloc. Le vrai bloc peut etre different a cause d'erreurs de precision de nos
        // nombres flottants (si z = 14.999 par exemple, et qu'il n'y a pas de blocs a la position
        // 14 (apres arrondi vers l'entier) on doit trouver et retourner le bloc en position 15 s'il existe
        // A cause des erreurs de precisions, ils arrive que le cote d'un bloc qui doit pourtant etre a la
        // position 15 par exemple nous retourne plutot la position 15.0001
        for(int x = px - 1; !found && x <= px + 1; ++x)
        {
            for(int y = py - 1; !found && y <= py + 1; ++y)
            {
                for(int z = pz - 1; !found && y >= 0  && z <= pz + 1; ++z)
                {
                        BlockType bt = BlockAt(x, y, z);

						if(bt == BTYPE_AIR)
                            continue;

                        m_currentBlock.x = x;
                        m_currentBlock.y = y;
                        m_currentBlock.z = z;

                        if(Tool::InRangeWithEpsilon<float>((float)posX, (float)x, (float)(x+1), 0.05f) && Tool::InRangeWithEpsilon<float>((float)posY,(float)y, (float)(y+1), 0.05f) && Tool::InRangeWithEpsilon<float>((float)posZ, (float)z, (float)(z+1), 0.05f))
                        {
                            found = true;
                        }
                }
            }
        }
    }

    if(!found)
    {
        m_currentBlock.x = ERROR_BLOCK_SELECTED;
    }
    else
    {
        // Find on which face of the bloc we got an hit
        m_currentFaceNormal.Zero();

        //Epsilon previously was set to 0.005f
		//However, this caused an incovenient bug so now it is set to 0.020f
        if(Tool::EqualWithEpsilon<float>((float)posZ, (float)m_currentBlock.z, 0.005f))
            m_currentFaceNormal.z = -1;//Back
        else if(Tool::EqualWithEpsilon<float>((float)posZ, (float)m_currentBlock.z + 1, 0.005f))
            m_currentFaceNormal.z = 1;//Front
        else if(Tool::EqualWithEpsilon<float>((float)posX, (float)m_currentBlock.x, 0.005f))
            m_currentFaceNormal.x = -1;//Left
        else if(Tool::EqualWithEpsilon<float>((float)posX, (float)m_currentBlock.x + 1, 0.005f))
            m_currentFaceNormal.x = 1;//Right
        else if(Tool::EqualWithEpsilon<float>((float)posY, (float)m_currentBlock.y, 0.005f))
            m_currentFaceNormal.y = -1;//Bottom
        else if(Tool::EqualWithEpsilon<float>((float)posY, (float)m_currentBlock.y + 1, 0.005f))
            m_currentFaceNormal.y = 1;//Top
    }
}

BlockType Engine::BlockAt(int x, int y, int z)
{
	if(y > CHUNK_SIZE_Y)
		return BTYPE_AIR;

	int cx = 0, cz = 0;
	Chunk* chunk = m_2dchunks.GetChunkOfPoint(x, z, &cx, &cz);

	return chunk->GetBloc(cx, y, cz);
}

void Engine::SetPause(bool pause) {
	m_pause = pause;
	if(!pause) {
		m_pausePictureTaked = false;

		if(m_pixels != 0) {
			delete [] m_pixels;
			m_pixels = 0;

			CenterMouse();
		}

		HideCursor();
	} else {
		ShowCursor();
	}
}

BlockType Engine::GetBlocAjout() const {
	return m_currentItemMenu->GetCurrentItemBlockType();
}

void Engine::Resized() {
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective( 45.0f, (float)Width() / Height(), 0.1f, 1000.0f);

	if(m_pause)
		m_showPicture = false;
	
	m_currentItemMenu->Center(Width(), Height());
	m_menuCoeur->Center(Width(), Height());
	MenuOptions::GetInstance()->Center(Width(), Height());
	MenuItem::GetInstance()->Center(Width(), Height());
	MenuPause::GetInstance()->Center(Width(), Height());
}

void Engine::OnViewDistanceChanged() {
	m_2dchunks.Resize();
}

void Engine::FocusChanged() {
	if(!m_haveFocus)
		MenuPause::GetInstance()->Show();
}
