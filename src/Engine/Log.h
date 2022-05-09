#pragma once

class Log
{
public:
   Log() = default;

   enum Level
   {
      ERROR,
      WARNING,
      INFO
   };

   void SetLevel(int level) { logLevel_ = level; }

   void Error(const char* message)
   {
      if (logLevel_ <= ERROR) {
         std::cout << "[ERROR]: " << message << std::endl;
      }
   }

   void Warn(const char* message)
   {
      if (logLevel_ >= WARNING) {
         std::cout << "[WARNING]: " << message << std::endl;
      }
   }

   void Info(const char* message)
   {
      if (logLevel_ >= INFO) {
         std::cout << "[INFO]: " << message << std::endl;
      }
   }

private:
   int logLevel_ = INFO;
};