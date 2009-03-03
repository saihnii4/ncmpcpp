/***************************************************************************
 *   Copyright (C) 2008-2009 by Andrzej Rybczak                            *
 *   electricityispower@gmail.com                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/

#ifndef _LYRICS_H
#define _LYRICS_H

#include "ncmpcpp.h"
#include "mpdpp.h"
#include "screen.h"

#ifdef HAVE_CURL_CURL_H
# include <pthread.h>
# include "curl/curl.h"
#endif

class Lyrics : public Screen<Scrollpad>
{
	struct Plugin
	{
		const char *url;
		const char *tag_open;
		const char *tag_close;
		bool (*not_found)(const std::string &);
	};
	
	public:
		Lyrics() : itsScrollBegin(0) { }
		~Lyrics() { }
		
		virtual void Init();
		virtual void Resize();
		virtual void SwitchTo();
		
		virtual std::string Title();
		
		virtual void Update();
		
		virtual void SpacePressed();
		
		virtual bool allowsSelection() { return false; }
		
		virtual List *GetList() { return 0; }
		
		void Edit();
		
		static bool Reload;
		
#		ifdef HAVE_CURL_CURL_H
		static const char *GetPluginName(int offset);
#		endif // HAVE_CURL_CURL_H
		
	private:
		static void *Get(void *);
		
		static std::string Filename;
		static const std::string Folder;
		
#		ifdef HAVE_CURL_CURL_H
		void Take();
		
		static const Plugin *ChoosePlugin(int);
		static bool LyricWiki_NotFound(const std::string &);
		static bool LyricsPlugin_NotFound(const std::string &);
		
		static bool Ready;
		static pthread_t Downloader;
		
		static const char *PluginsList[];
		static const Plugin LyricWiki;
		static const Plugin LyricsPlugin;
#		endif // HAVE_CURL_CURL_H
		
		size_t itsScrollBegin;
		MPD::Song itsSong;
};

extern Lyrics *myLyrics;

#endif

