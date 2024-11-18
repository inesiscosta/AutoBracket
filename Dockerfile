FROM arm64v8/debian:trixie-slim
RUN apt update
RUN apt install -y gcc nano valgrind binutils make gdb git g++
