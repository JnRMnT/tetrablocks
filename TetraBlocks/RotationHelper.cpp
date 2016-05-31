#include "RotationHelper.h"
#include "Block.h"

Uint16 RotationHelper::stateList[7][4];
RotationHelper::RotationHelper()
{
	Uint16 I_state_list[4] = { 0x4444, 0x0F00, 0x2222, 0x00F0 };
	Uint16 J_state_list[4] = { 0x44C0, 0x8E00, 0x6440, 0x0E20 };
	Uint16 L_state_list[4] = { 0x4460, 0xE800, 0XC440, 0X2E00 };
	Uint16 O_state_list[4] = { 0xCC00, 0xCC00, 0xCC00, 0xCC00 };
	Uint16 S_state_list[4] = { 0x06C0, 0x8C40, 0x6C00, 0x4620 };
	Uint16 T_state_list[4] = { 0x0E40, 0x4C40, 0x4E00, 0x4640 };
	Uint16 Z_state_list[4] = { 0x0C60, 0x4C80, 0xC600, 0x2640 };

	RotationHelper::stateList[0][0] = I_state_list[0];
	RotationHelper::stateList[0][1] = I_state_list[1];
	RotationHelper::stateList[0][2] = I_state_list[2];
	RotationHelper::stateList[0][3] = I_state_list[3];
	RotationHelper::stateList[1][0] = J_state_list[0];
	RotationHelper::stateList[1][1] = J_state_list[1];
	RotationHelper::stateList[1][2] = J_state_list[2];
	RotationHelper::stateList[1][3] = J_state_list[3];
	RotationHelper::stateList[2][0] = L_state_list[0];
	RotationHelper::stateList[2][1] = L_state_list[1];
	RotationHelper::stateList[2][2] = L_state_list[2];
	RotationHelper::stateList[2][3] = L_state_list[3];
	RotationHelper::stateList[3][0] = O_state_list[0];
	RotationHelper::stateList[3][1] = O_state_list[1];
	RotationHelper::stateList[3][2] = O_state_list[2];
	RotationHelper::stateList[3][3] = O_state_list[3];
	RotationHelper::stateList[4][0] = S_state_list[0];
	RotationHelper::stateList[4][1] = S_state_list[1];
	RotationHelper::stateList[4][2] = S_state_list[2];
	RotationHelper::stateList[4][3] = S_state_list[3];
	RotationHelper::stateList[5][0] = T_state_list[0];
	RotationHelper::stateList[5][1] = T_state_list[1];
	RotationHelper::stateList[5][2] = T_state_list[2];
	RotationHelper::stateList[5][3] = T_state_list[3];
	RotationHelper::stateList[6][0] = Z_state_list[0];
	RotationHelper::stateList[6][1] = Z_state_list[1];
	RotationHelper::stateList[6][2] = Z_state_list[2];
	RotationHelper::stateList[6][3] = Z_state_list[3];
}


RotationHelper::~RotationHelper()
{
	free(stateList);
}

Uint16* RotationHelper::GetBlockStates(BlockType blockType)
{
	return stateList[(int)blockType];
}

Uint16 RotationHelper::GetBlockState(BlockType blockType, int index)
{
	Uint16* block_states = GetBlockStates(blockType);
	return *(block_states + index);
}


int RotationHelper::GetStateIndex(BlockType blockType, Uint16 currentState)
{
	int i = 0;
	Uint16* blockStates = GetBlockStates(blockType);
	while (i < 4)
	{
		Uint16 state = *(blockStates + i);
		if (state == currentState)
		{
			return i;
		}
		i++;
	}

	return 0;
}

Uint16 RotationHelper::GetNext(BlockType blockType, Uint16 currentState)
{
	int currentIndex = GetStateIndex(blockType, currentState);
	int newIndex = (currentIndex + 1) % 4;
	return GetBlockState(blockType, newIndex);
}

Uint16 RotationHelper::GetPrevious(BlockType blockType, Uint16 currentState)
{
	int currentIndex = GetStateIndex(blockType, currentState);
	int newIndex = currentIndex - 1;
	if (newIndex < 0)
	{
		newIndex += 4;
	}

	return GetBlockState(blockType, newIndex);
}

bool RotationHelper::CanRotateTo(Grid* grid, Block* block, Uint16 state)
{
	Uint16 partial_status = grid->GetPartialStatus(block->GetCenterY(), block->GetCenterX(), block->GetState());
	return (~partial_status) & block->GetState() == block->GetState();
}
