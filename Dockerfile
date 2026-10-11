# Multi-stage Dockerfile for SudharshanMart (C++20 Native Backend)
# Stage 1: Build environment with full C++20 toolchain and vcpkg
FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    curl \
    zip \
    unzip \
    tar \
    pkg-config \
    libsqlite3-dev \
    libsodium-dev \
    libcurl4-openssl-dev \
    libssl-dev \
    uuid-dev \
    zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

# Configure and build Release binary
RUN cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build --config Release

# Stage 2: Minimal runtime image (debian:bookworm-slim)
FROM debian:bookworm-slim AS runtime

RUN apt-get update && apt-get install -y \
    sqlite3 \
    libsodium23 \
    libcurl4 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt/sudharshanmart

# Copy compiled executable and static public assets
COPY --from=builder /app/build/sudharshanmart /opt/sudharshanmart/bin/sudharshanmart
COPY --from=builder /app/public /opt/sudharshanmart/public
COPY --from=builder /app/db /opt/sudharshanmart/db

ENV PORT=8080
ENV AI_CHATBOT_PROVIDER=mock
EXPOSE 8080

ENTRYPOINT ["/opt/sudharshanmart/bin/sudharshanmart"]
