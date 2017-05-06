#ifndef ENUMTYPE_H
#define ENUMTYPE_H
#include "definitions.h"
#include <cstdint>
NS_EM_BEGIN
enum class Prop: int32_t
{
	empty = 0,
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
	shovel = 53,
	hammer = 54,
	pickaxe = 55,
	airUnit = 56
};
enum class EdgeType :int32_t
{
	empty = 0,
	badWall = 1,
	dirtWall = 2,
	woodenWall = 3,
	ironWall = 4,
	pressureDoor = 5,
	letterDoor = 6,
	oneWayLetterDoor = 7,
	conditionDoor = 8,
	oneWayDoor = 9,
	timesLimitedDoor = 10,
	oneWayTimesLimitedDoor = 11
};
enum class EventType : int32_t
{
	empty = 0,
	playerOutOfRange = 1,
	playerLose = 2,
	playerWin = 3,
	playerPickUpProp = 4,
	playerUseProp = 5,
	playerHaveNoPermition = 6,
	playerMoveFailed = 7,
	playerMoveSuccessfully = 8,
	playerTeleported = 9,
	playerHaveNoProp = 10,
	cannotInteractive = 11
};
enum class NodeType :int32_t
{
	empty = 0,
	startPoint = 1,
	endPoint = 2,
	teleportPoint = 3,
	lava = 4
};
NS_EM_END
#endif