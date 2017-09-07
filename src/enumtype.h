#ifndef ENUMTYPE_H
#define ENUMTYPE_H
#include "definitions.h"
#include <cstdint>
#include <string>
NS_EM_BEGIN
enum class Prop: int32_t
{
	empty = 0,
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
	shovel = 53,
	hammer = 54,
	pickaxe = 55,
	airUnit = 56,
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
	oneWayLetterDoor0 = 7,
	oneWayLetterDoor1 = 8,
	conditionDoor = 9,
	oneWayDoor0 = 10,
	oneWayDoor1 = 11,
	timesLimitedDoor = 12,
	oneWayTimesLimitedDoor0 = 13,
	oneWayTimesLimitedDoor1 = 14,
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
	cannotInteractive = 11,
};
const std::string eventInformationText[12]=
{	"NULL",
	"player out of range!",
	"player Lose!",
	"player Win!",
	"player picked up a prop",
	"player used a prop",
	"player have no permition",
	"player moved failed",
	"player moved successful",
	"player teleported",
	"player has no prop",
	"cannot interactive"
};
enum class NodeType :int32_t
{
	empty = 0,
	startPoint = 1,
	endPoint = 2,
	teleportPoint = 3,
	lava = 4,
};
NS_EM_END
#endif
