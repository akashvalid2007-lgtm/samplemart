# Sprint Retrospectives (RETRO.md)

### Sprint 1 (Jul 27 – Aug 9)
- **What worked**: Fast architecture bootstrapping using Drogon and pure C++ repository interfaces with RAII.
- **What didn't**: Linking SQLite and libsodium on Windows required precise CMake toolchain flags.
- **One change for next sprint**: Use vcpkg manifest mode for all external library dependencies consistently.

### Sprint 2 (Aug 10 – Aug 23)
- **What worked**: Clean separation of DTOs and entities ensured no sensitive fields (like password hashes) leaked to JSON.
- **What didn't**: Seller and admin permission checks were initially scattered across controllers.
- **One change for next sprint**: Centralize role validations in service orchestration methods and BaseController.

### Sprint 3 (Aug 24 – Sep 6)
- **What worked**: Parameterized SQL queries completely eliminated SQL injection risks; zero compiler warnings under `-Wall -Wextra`.
- **What didn't**: Complex queries for seller revenue calculations needed careful indexing.
- **One change for next sprint**: Added composite indexes on foreign keys and status columns in migration V3.

### Sprint 4 (Sep 7 – Sep 20)
- **What worked**: Multi-stage Docker container produces a lightweight 80MB runtime image on Debian bookworm-slim.
- **What didn't**: Systemd service initially had file permission issues with the SQLite `.db-wal` journal files.
- **One change for next sprint**: Explicitly run systemd service under dedicated user with proper permissions on the data directory.

### Sprint 5 (Sep 21 – Oct 10)
- **What worked**: AI ChatProvider abstraction allowed seamless toggling between Gemini and canned Mock provider for offline demos.
- **What didn't**: Per-session rate limits required a mutex to prevent race conditions during concurrent chat queries.
- **One change for next sprint**: Used `std::mutex` guard around session timestamp deque and cache map.
