#include "stdafx.h"
#include "TradeMenu.h"
#include "libtcod.hpp"
#include "StateManager.h"
#include "globals.h"
#include "ConsoleUtil.h"

TradeMenu::TradeMenu()
{
	mState = MAIN;
	mMenuX = WIDTH / 8 ;
	mMenuW = WIDTH / 4 * 3;
	mWormSelection = 0;
	mTradeSelection = 0;
	mTotalCost = 0;
	mAmt = 0;
}

TradeMenu::~TradeMenu()
{
}

void TradeMenu::updateMain()
{
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch (key.vk) {
	case TCODK_ENTER:
		if (mTradeSelection < 2)
		{
			makeTransaction();
		}
		else if (mTradeSelection == 2)
		{
			STATE_MANAGER->runState(BOAT_EDITOR);
		}
		else if (mTradeSelection == 3)
		{
			STATE_MANAGER->runState(REGION_SELECT);
		}
		break;
	case TCODK_ESCAPE:
		toQuit = true;
		break;
	case TCODK_UP:
		mWormSelection--;
		break;
	case TCODK_DOWN:
		mWormSelection++;
		break;
	case TCODK_LEFT:
		mTradeSelection--;
		break;
	case TCODK_RIGHT:
		mTradeSelection++;
		break;
	default:
		break;
	}

	switch (key.c) {
	case 'm': 
		tradeMaxAmt = !tradeMaxAmt; 
		break;
	case 'a':
		mAmt -= 1;
		break;
	case 's':
		mAmt -= 10;
		break;
	case 'd':
		mAmt -= 100;
		break;
	case 'f':
		mAmt -= 1000;
		break;

	case 'h':
		mAmt += 1;
		break;
	case 'j':
		mAmt += 10;
		break;
	case 'k':
		mAmt += 100;
		break;
	case 'l':
		mAmt += 1000;
		break;
	default: break;
	}

	if (mAmt <= 0)
		mAmt = 0;
	if (mWormSelection < 0)
		mWormSelection = wormVariationContainer.size()-1;
	if (mWormSelection > wormVariationContainer.size()-1)
		mWormSelection = 0;
	if (mTradeSelection < 0)
		mTradeSelection = 3;
	if (mTradeSelection > 3)
		mTradeSelection = 0;
}

void TradeMenu::updateBuy()
{
	if (tradeMaxAmt)
	{
		mAmt = (int)((coinPouch/wormVariationContainer[mWormSelection]->getValue()));
	}
	if (coinPouch < (int)((wormVariationContainer[mWormSelection]->getValue()*mAmt*regionContainer[currentRegion]->getRegionDemand(mWormSelection))))
		mAmt = (int)((wormVariationContainer[mWormSelection]->getValue()) *regionContainer[currentRegion]->getRegionDemand(mWormSelection) / coinPouch);
	mTotalCost = wormVariationContainer[mWormSelection]->getValue()* mAmt*regionContainer[currentRegion]->getRegionDemand(mWormSelection);
	totalMoneyStr =  "BUYING -> Total Amount: " + std::to_string(mTotalCost);
}

void TradeMenu::updateSell()
{
	if (tradeMaxAmt)
	{
		mAmt = regionContainer[mWormSelection]->getWormBankNotes();
	}

	if (mAmt > (regionContainer[mWormSelection]->getWormBankNotes()))
		mAmt = regionContainer[mWormSelection]->getWormBankNotes();
	mTotalCost = wormVariationContainer[mWormSelection]->getValue()* mAmt*regionContainer[currentRegion]->getRegionDemand(mWormSelection);
	totalMoneyStr = "SELLING -> Total Amount: " + std::to_string(mTotalCost);
}

void TradeMenu::drawMain()
{
	int movementFactor = 5;
	TCODColor originalColor = TCODConsole::root->getDefaultForeground();
	
	
	
	//drawBox((mTradeSelection + 1) * (movementFactor*6),2 , mMenuX, movementFactor, true, TCODColor::grey);
	drawBox(mMenuX + (mTradeSelection + 1) * mMenuW / 4 - mMenuW / 8 - mMenuW / 16 - mTradeSelection - 1, 2, mMenuW / 8 + 1, movementFactor, true, TCODColor::darkGreen);
	
	std::string s;
	TCODConsole::root->setDefaultForeground(TCODColor::darkGreen);
	s = "BUY";
	TCODConsole::root->print(mMenuX + mMenuW / 8 * 1 - s.length() / 2, movementFactor*.8, s.c_str());
	s = "SELL";
	TCODConsole::root->print(mMenuX + mMenuW / 8 * 3 - s.length() / 2, movementFactor*.8, s.c_str());
	s = "BOAT";
	TCODConsole::root->print(mMenuX + mMenuW / 8 * 5 - s.length() / 2, movementFactor*.8, s.c_str());
	s = "TRAVEL";
	TCODConsole::root->print(mMenuX + mMenuW / 8 * 7 - s.length() / 2, movementFactor*.8, s.c_str());
	if (mTradeSelection < 2)
	{
		//box for worm selection
		drawBox(mMenuX + 2, (mWormSelection + 1) * movementFactor - 2 + (HEIGHT * .2), mMenuW - 4, movementFactor, true, TCODColor::darkGreen);
		s = "PINKER-THAN-PINK";
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 4, s.c_str());
		s = "CRIMSON";
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 5, s.c_str());
		s = "EMERALD";
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 6, s.c_str());
		s = "CYAN";
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 7, s.c_str());
		s = "RAINBOW";
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 8, s.c_str());

		TCODConsole::root->setDefaultForeground(TCODColor::grey);
		s = "QUANTITY OF ITEMS: " + std::to_string(mAmt);
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 9, s.c_str());

		s = "TOTAL VALUE OF BULK: " + totalMoneyStr;
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 10, s.c_str());

		s = "YOUR COIN POUCH: " + std::to_string(coinPouch);
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 11, s.c_str());

		s = "A: -1 S: -10 D: -100 F:-1000";
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 12, s.c_str());

		s = "H: +1 J: +10 K: +100 L: +1000";
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 13, s.c_str());
		TCODConsole::root->setDefaultForeground(originalColor);
	}
	else if (mTradeSelection == 2)
	{
		std::string s = "Press ENTER to modify your boat!";
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 4, s.c_str());
	}
	else if(mTradeSelection == 3)
	{
		std::string s = "Press ENTER to travel to another region!";
		TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, movementFactor * 4, s.c_str());
	}
}

bool TradeMenu::checkClearPos()
{
	return false;
}

void TradeMenu::makeTransaction()
{
	if (mTradeSelection == 0)
	{
		coinPouch -= mTotalCost;
		regionContainer[mWormSelection]->addBankNotes(mAmt);
	}
	else
	{
		coinPouch += mTotalCost;
		regionContainer[mWormSelection]->subtractBankNotes(mAmt);
	}
		
}

void TradeMenu::run()
{
	toQuit = false;
	while (!TCODConsole::isWindowClosed() && !toQuit)
	{
		update();
		render();
	}
}

void TradeMenu::update()
{
	updateMain();
	if (mTradeSelection == 0)
		updateBuy();
	else if (mTradeSelection == 1)
		updateSell();
}

void TradeMenu::render()
{
	TCODConsole::root->clear();
	TCODColor originalColor = TCODConsole::root->getDefaultForeground();

	drawWater();
	//drawBox(mMenuX, 1, mMenuW, HEIGHT / 4 * 3, true, TCODColor::red);
	backgroundFill(mMenuX, 1, mMenuW, HEIGHT * .9, TCODColor::darkestGreen);
	fillWithChar(mMenuX , 1, mMenuW , HEIGHT * .9 , ' ');
	drawBox(mMenuX, 1, mMenuW, HEIGHT * .9, true, TCODColor::darkGreen);

	//backgroundFill(mMenuX, 1, mMenuW, HEIGHT *.3, TCODColor::darkestGreen);
	//fillWithChar(mMenuX, 1, mMenuX, (HEIGHT * .15)  , ' ');
	//fillWithChar(mMenuX, 1, mMenuW - 1, HEIGHT - 2, ' ');
	//backgroundFill(mMenuX, 1, mMenuW, HEIGHT / 4 * 3,  TCODColor::darkestGreen);
	//fillWithChar(mMenuX + 1, 2, mMenuW - 2, HEIGHT - 4, ' ');
	//fillWithChar(mMenuX + 1, 2, mMenuW - 2, HEIGHT / 4 * 3 - 2, ' ');
	std::string s = " TRADE MENU ";
	TCODConsole::root->setDefaultForeground(TCODColor::darkGreen);
	TCODConsole::root->print(mMenuX + mMenuW / 2 - s.length() / 2, 1, s.c_str());

	drawMain();

	TCODConsole::root->setDefaultForeground(originalColor);
	TCODConsole::flush();
}
