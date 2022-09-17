// TODO: implement crappy logging system so I can keep track of what the hell is
// going on
//       inside ncmpcpp

#include "screen.h"

using Global::MainHeight;
using Global::MianStartY;

Logger *myLogger;

Logger::Logger()
    : Screen(NC::ScrollPad(0, MainStartY, COLS, MainHeight, "",
                           Config.main_color, NC::Border())),
      m_refresh_window(false), m_scroll_begin(0), m_fetcher(nullptr) {}

void Logger::resize() {
  size_t x_offset, width;
  getWindowResizeParams(x_offset, width);
  w.resize(width, MainHeight);
  w.moveTo(x_offset, MainStartY);
  hasToBeResized = 0;
}

void Logger::update() {

  auto buffer = m_shared_buffer->acquire();
  if (m_worker.valid()) {
    auto buffer = m_shared_buffer->acquire();
    if (!buffer->empty()) {
      w << *buffer;
      buffer->clear();
      m_refresh_window = true;
    }

    if (m_worker.is_ready()) {
      auto lyrics = m_worker.get();
      if (lyrics) {
        w.clear();
        w << Charset::utf8ToLocale(*lyrics);
        std::string filename = lyricsFilename(m_song);
        if (!saveLyrics(filename, *lyrics))
          Statusbar::printf("Couldn't save lyrics as \"%1%\": %2%", filename,
                            strerror(errno));
      } else
        w << "\nLyrics were not found.\n";
      clearWorker();
      m_refresh_window = true;
    }
  }

  if (m_refresh_window) {
    m_refresh_window = false;
    w.flush();
    w.refresh();
  }
}
