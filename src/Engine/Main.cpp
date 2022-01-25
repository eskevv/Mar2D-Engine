#include "Engine.h"

int main(int argc, char* argv[])
{
   Engine engine;

   engine.Initialize();
   engine.Run();
   engine.Quit();

   return 0;
}