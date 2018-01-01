#pragma once
#include "State.h"
#include <stdio.h>
#include <iostream>
#include "region.h"
#include "worm.h"

class TradeMenu : public State
{
	enum EditorState {
		MAIN,
		SELL,
		BUY, 
		TRADE
	};
	/***** ATTRIBUTES *****/
	EditorState mState;
	int mCursorX, mCursorY;
	int mMenuX, mMenuW;
	int mWormSelection;
	int mTradeSelection;
	int mAmt;
	bool tradeMaxAmt = false;
	float mTotalCost;
	std::string totalMoneyStr = "";

	/***** CONSTRUCTOR / DESTRUCTOR *****/
public:
	/// The default constructor
	TradeMenu();

	/// The destructor.  
	~TradeMenu();

	/***** METHODS *****/
protected:
	void updateMain();
	void updateBuy();
	void updateSell();
	void drawMain();
	bool checkClearPos();
	void makeTransaction();

public:
	void run();
	void update();
	void render();

};