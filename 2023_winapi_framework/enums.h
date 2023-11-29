#pragma once

enum class KEY_STATE
{
	// NONE: �ȴ���
	// DOWN: �� ����
	// UP: ��
	// PRESS: ��������
	NONE, DOWN, UP, PRESS
};

enum class KEY_TYPE
{
	LEFT, RIGHT, UP, DOWN,
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,H,J,K,L,
	Z,X,C,V,B,N,M,
	CTRL, LALT, LSHIFT, SPACE,
	ENTER, TAB, ESC, LBUTTON, RBUTTON, LAST
	// LAST�ǹ�: ���̶�� ���̾�
};

enum class OBJECT_GROUP
{
	DEFAULT,
	TILE,
	BACKGROUNDOBJECT,
	PARTICLE,
	UI,
	STAR,
	DEBUG,
	DOTWEEN,
	END = 30
};

enum class PEN_TYPE
{
	HOLLOW, RED, GREEN, 
	BLUE, YELLOW, END
};

enum class BRUSH_TYPE
{
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};

enum class EVENT_TYPE
{
	DELETE_OBJECT,
	CREATE_OBJECT,
	SCENE_CHANGE,
	END
};

enum class TILE_TYPE
{
	WATER, FIRE, GRASS
	, FIRELOCK, WATERLOCK, GRASSLOCK
	, TELEPORT
	, MOVELU, MOVEL, MOVELD
	, MOVERU, MOVER, MOVERD
	, WIND
	, END
};

enum class TILE_STATE
{
	DEFAULT,
	NOTSELECT,
	CANMOVE,
	END
};

enum class DOTWEEN_TYPE
{
	MOVE,
	SCALE,
	ROTATE,
	FADE,
	END
};

struct XY
{
	int xidx;
	int yidx;
};