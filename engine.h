#ifndef ENGINE_H__
#define ENGINE_H__

#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "define.h"
#include "tool.h"
#include "openglcontext.h"
#include "texture.h"
#include "player.h"
#include "shader.h"
#include "chunk.h"
#include "textureatlas.h"
#include "vector3.h"
#include "blockinfoencapsuler.h"
#include "blockinfo.h"
#include "array2d.h"
#include "chunkencapsuler.h"
#include "movableentity.h"
#include "menucurrentitem.h"
#include "menucoeur.h"

#include "chunkmesh.h"
#include "mobhandler.h"

class Engine : public OpenglContext
{
public:
    Engine();
    virtual ~Engine();
    virtual void Init();
    virtual void DeInit();
    virtual void LoadResource();
    virtual void UnloadResource();
    virtual void Render(float elapsedTime);
    virtual void KeyPressEvent(unsigned char key);
    virtual void KeyReleaseEvent(unsigned char key);
    virtual void MouseMoveEvent(int x, int y);
    virtual void MousePressEvent(const MOUSE_BUTTON &button, int x, int y);
    virtual void MouseReleaseEvent(const MOUSE_BUTTON &button, int x, int y);
	virtual void MouseWheelEvent(const MOUSE_BUTTON &button, int delta);
	virtual void Resized();
	virtual void FocusChanged();

	void OnViewDistanceChanged();

	void DrawHud(float elapsedTime);
	void Collision(MovableEntity* entity);
	int GetFps();
	void GetBlocAtCursor();
	void DrawFaceColor();
	BlockType BlockAt(int x, int y, int z);
	std::string GetBlockType();	
	
	void SetPause(bool pause);
	bool IsPaused() const;

	uint8* GetScreenshot() const;

	BlockType GetBlocAjout() const;

	ChunkEncapsuler* GetChunks() { return &m_2dchunks; }

	static Engine* GetInstance();

private:
    bool LoadTexture(Texture& texture, const char* filename, bool stopOnError = true);

private:
	static Engine* m_instance;

    bool m_wireframe, m_showDebug;

    bool m_pause, m_pausePictureTaked, m_showPicture;
	unsigned char* m_pixels;

	Texture m_textureCrosshair;
	Player m_player;
	Shader m_shader01;
	ChunkEncapsuler m_2dchunks;
	Vector3i m_currentBlock,  m_currentFaceNormal;
	BlockInfoEncapsuler* m_blockInfos;
	bool m_wPressed, m_aPressed, m_sPressed, m_dPressed;
	
	MenuCurrentItem* m_currentItemMenu;
	MenuCoeur* m_menuCoeur;
	//MobHandler* m_mobHandler;
};

#endif // ENGINE_H__
