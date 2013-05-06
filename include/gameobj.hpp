#include "common.h"

class Graphics;

class GameObj
{
	public:
		GameObj();
		void create();
		void destroy();
		void update();
		void draw(Graphics *graphics);
};