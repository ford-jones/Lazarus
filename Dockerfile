FROM gcc:latest

WORKDIR /app

COPY . .

RUN apt-get update
RUN apt install mesa-common-dev -y
RUN apt install libglfw3-dev -y
RUN apt install libglm-dev -y
RUN apt install libglew-dev -y
RUN apt install libstb-dev -y

RUN make run

CMD ./run


