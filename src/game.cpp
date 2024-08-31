#include "game.h"
#include "defines.h"
#include "misc_util.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
/* -------------------------------------------------------------------------- */
Game::Game() : window_(sf::VideoMode(800, 600), "LMent") {
  // TODO should I maybe find another way of error handling?
  if (initialize_logging() == false) {
    exit();
  }

  isRunning_ = true;
}
/* -------------------------------------------------------------------------- */
void Game::run() {
  while (isRunning_) {
    poll_events();
    update();
    draw();
  }

  exit();
}
/* -------------------------------------------------------------------------- */
bool Game::initialize_logging() {
  // Try/catch blocks and smart pointers are used here because of the lib API
  try {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(LOG_LEVEL);
    console_sink->set_pattern(
        "[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        "logs/LMent_" + util::current_datetime_as_string() + ".log", true);
    file_sink->set_level(spdlog::level::trace);

    spdlog::sinks_init_list sink_list = {file_sink, console_sink};

    spdlog::logger logger("multi_sink", sink_list.begin(), sink_list.end());
    logger.set_level(LOG_LEVEL);

    // or you can even set multi_sink logger as default logger
    spdlog::set_default_logger(std::make_shared<spdlog::logger>(
        "multi_sink", spdlog::sinks_init_list({console_sink, file_sink})));

    spdlog::info("Logging library successfully initialized");

  } catch (const spdlog::spdlog_ex &ex) {
    std::fprintf(stderr, "Log initialization failed: %s\n", ex.what());
    std::fflush(stderr);
    return false;
  }

  return true;
}
/* -------------------------------------------------------------------------- */
void Game::exit() { spdlog::info("Exiting the game."); }
/* -------------------------------------------------------------------------- */
void Game::poll_events() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      // TODO Don't do any logic here, broadcast signals instead.
      isRunning_ = false;
  }
}
/* -------------------------------------------------------------------------- */
void Game::update() {
  // TODO add logic code.
}
/* -------------------------------------------------------------------------- */
void Game::draw() {
  window_.clear();
  // Drawing code here
  window_.display();
}
/* -------------------------------------------------------------------------- */