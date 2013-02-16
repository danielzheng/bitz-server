/*
 *	bitz-server, An ICAP server implementation in C++
 *	Copyright (C) 2012	Uditha Atukorala
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef BITZ_CONFIG_H
#define BITZ_CONFIG_H

#include <string>
#include <libconfig.h++>


#ifndef BITZ_SERVER_CONFIG_FILE
#define BITZ_SERVER_CONFIG_FILE "/etc/bitz/bitz-server.conf"
#endif

namespace bitz {

	struct config_t {
		int port;
		std::string log_file;
		std::string log_category;
	};

	class Config {
	public:
		static Config &instance() {
			static Config config;
			return config;
		}

		const config_t &initialise( const std::string &config_file = BITZ_SERVER_CONFIG_FILE );
		const config_t &configs();

		/**
		*   Returns module specific config settings (or NULL if not found)
		*   Note: This method should be only used my the pluggable modules and not
		*         by the core code.
		*
		*   @param module module name
		*   @return module config settings
		*/
		const libconfig::Setting * module_configs( const std::string &module );

	private:
		config_t _config;
		libconfig::Config * _lconfig;

		Config();
		~Config();
		Config( Config const &copy );
		Config &operator=( const Config &copy );
	};

} /* end of namespace bitz */

#endif /* !BITZ_CONFIG_H */

