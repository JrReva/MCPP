#ifndef DEFINE_H__
#define DEFINE_H__

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#ifdef _WIN32
#include <windows.h>
#include <ShlObj.h>
#endif

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 128
#define CHUNK_SIZE_Z 16

typedef uint8 BlockType;

#define IN_DEBUG						false

#if _DEBUG
#define TEXTURE_PATH           "../MCPP/media/textures/"
#define SHADER_PATH            "../MCPP/media/shaders/"
#define SAVE_CHUNKS_PATH       "/MCPP/media/chunks/"
#define MESH_PATH				"../MCPP/media/mesh/"
#define SOUND_PATH				"../MCPP/media/sound/"
#define MUSIC_PATH				"../MCPP/media/music/"
#else
#define TEXTURE_PATH           "./media/textures/"
#define SHADER_PATH            "./media/shaders/"
#define SAVE_CHUNKS_PATH       "/MCPP/media/chunks/"
#define SAVE_CHUNKS_PATH       "./media/chunks/"
#define SOUND_PATH				"./media/sound/"
#define MUSIC_PATH				"./media/music/"
#endif

#define ERROR_BLOCK_SELECTED			2147483647

#define WINDOW_NAME						"MineClone PlusPlus"
#define DEFAULT_WIDTH					1024
#define DEFAULT_HEIGHT					768

//World generation
//Water
#define WATER_LEVEL						54

//Sand
#define SAND_MIN_LEVEL					46
#define SAND_MAX_LEVEL					56
#define BEACH_RADIUS					3
#define SAND_DEPTH						4

#define STONE_LEVEL						4

#define MM_DIVISION						7
#define MAX_SELECTION_DISTANCE			10
#define HAUTEUR_PLANCHER				50 
#define HAUTEUR_JOUEUR					1.7f
#define HAUTEUR_CAMERA					1.5f
#define LARGEUR_JOUEUR                  0.30f

#define SAUT_WAITTIME					0.4f

#define SAUT_PERSO						6.8f	//Velocite initiale
#define VITESSE_DEPLACEMENT				0.3f	//En m/s
#define GRAVITY							-20		//En m/s
#define PLAYER_SPEED					3		//En m/s
#define PLAYER_RUNNING_SPEED			5		//En m/s
#define PLAYER_FLYING_SPEED				15		//En m/s
#define PLAYER_DAMAGE					10

#define MAX_FPS							60
#define SECOND_BY_CHUNK_LOAD			0.05f
#define SECOND_BY_CHUNK_UPDATE			0.1f
#define CHUNK_ENCAPSULER_CENTER_REFRESH 1.0f
#define MAX_VERTEX_BY_CHUNK				32768
#define PLAYER_START_HEIGHT				128

#define EPSILON							0.001f

#define WORLD_CENTER                    0
#define PLAYER_LIFE						20

#define WORLD_SEED						5927107
#define TREE_GENERATION_RATE			10		// / 1000

// HUD
#define NUMBER_CURRENT_ITEMS			9
#define ITEM_CASE_SIZE					75
#define COEUR_SIZE						25

//MOBS
#define MOBS_CLEANUP_DELAY				2
#define MOBS_MAX						10
#define KNOCKBACK_DURATION				2.f     //en s

#endif // DEFINE_H__
