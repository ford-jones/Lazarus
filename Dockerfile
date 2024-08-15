FROM gcc:latest

WORKDIR /app

RUN apt-get update
RUN apt-get install apt-utils -y
RUN apt install mesa-common-dev -y
RUN apt install libglfw3-dev -y
RUN apt install libglm-dev -y
RUN apt install libglew-dev -y
RUN apt install libstb-dev -y

RUN mv /usr/include/stb/stb_image.h /usr/local/include/stb_image.h

COPY . .

CMD make run