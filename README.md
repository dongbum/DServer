# DServer2
[![Build Status](https://travis-ci.com/dongbum/DServer.svg?branch=master)](https://travis-ci.com/dongbum/DServer)
[![Build status](https://ci.appveyor.com/api/projects/status/pn6fgpol4pg1f7mf?svg=true)](https://ci.appveyor.com/project/dongbum/dserver)
[![Coverage Status](https://coveralls.io/repos/github/dongbum/DServer/badge.svg?branch=master)](https://coveralls.io/github/dongbum/DServer?branch=master)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/dongbum/DServer.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/dongbum/DServer/context:cpp)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/dongbum/DServer.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/dongbum/DServer/alerts/)

Game server project.
This is not yet release version.

### Concept
Cross-platform game server using Boost.ASIO.

### Requirement
* VS2019 for MS Windows
* GCC 7.4.0 for Linux (Tested on Ubuntu 18.04)
* C++11 complier
* Boost 1.70 or above
* CMake

### Implement
* TCP game server
* Log manager
* MySQL connector
* Redis connector
* HTTP server (for monitoring)
* User define TCP protocol
* User define HTTP protocol

### Whats next
* RESTful API for monitoring
* Save log file to NoSQL system

### Opensource Licence
* jsoncpp (https://github.com/open-source-parsers/jsoncpp)
