
CC = g++
CFLAGS = -std=c++11 -Wall
TARGET = ./bin/server

BIN_DIR = ./obj

SRC_DIR = ./src
INCLUDE_DIR = ./include
LIB_DIR = ./libs

BIN_FILES = ${BIN_DIR}/main.o \
			${BIN_DIR}/model.o \
			${BIN_DIR}/model_card.o \
			${BIN_DIR}/model_deck.o \
			${BIN_DIR}/model_game.o \
			${BIN_DIR}/model_player.o \
			${BIN_DIR}/service_game.o \
			${BIN_DIR}/service_deck.o \
			${BIN_DIR}/service_player.o \
			${BIN_DIR}/service.o \
			${BIN_DIR}/storage.o \
			${BIN_DIR}/factory_deck.o \
			${BIN_DIR}/factory_game.o \
			${BIN_DIR}/factory_player.o \
			${BIN_DIR}/serializer_player.o \
			${BIN_DIR}/serializer_deck.o \
			${BIN_DIR}/serializer_game.o \

${TARGET}: ${BIN_FILES}
	${CC} ${CFLAGS} -o ${TARGET} ${BIN_DIR}/*.o

# Model binaries
${BIN_DIR}/main.o: ${SRC_DIR}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -I ${LIB_DIR} -c ${SRC_DIR}/main.cpp -o ${BIN_DIR}/main.o

${BIN_DIR}/model.o: ${INCLUDE_DIR}/models/Model.hpp ${SRC_DIR}/models/Model.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/models/Model.cpp  -o ${BIN_DIR}/model.o

${BIN_DIR}/model_card.o: ${INCLUDE_DIR}/models/Card.hpp ${SRC_DIR}/models/Card.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/models/Card.cpp  -o ${BIN_DIR}/model_card.o

${BIN_DIR}/model_deck.o: ${INCLUDE_DIR}/models/Deck.hpp ${SRC_DIR}/models/Deck.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/models/Deck.cpp  -o ${BIN_DIR}/model_deck.o

${BIN_DIR}/model_game.o: ${INCLUDE_DIR}/models/Game.hpp ${SRC_DIR}/models/Game.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/models/Game.cpp  -o ${BIN_DIR}/model_game.o

${BIN_DIR}/model_player.o: ${INCLUDE_DIR}/models/Player.hpp ${SRC_DIR}/models/Player.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/models/Player.cpp  -o ${BIN_DIR}/model_player.o

# Services binaries 
${BIN_DIR}/service_deck.o: ${INCLUDE_DIR}/services/DeckService.hpp ${SRC_DIR}/services/DeckService.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/services/DeckService.cpp  -o ${BIN_DIR}/service_deck.o

${BIN_DIR}/service_game.o: ${INCLUDE_DIR}/services/GameService.hpp ${SRC_DIR}/services/GameService.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/services/GameService.cpp  -o ${BIN_DIR}/service_game.o

${BIN_DIR}/service_player.o: ${INCLUDE_DIR}/services/PlayerService.hpp ${SRC_DIR}/services/PlayerService.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/services/PlayerService.cpp  -o ${BIN_DIR}/service_player.o

${BIN_DIR}/service.o: ${INCLUDE_DIR}/services/Service.hpp ${SRC_DIR}/services/Service.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/services/Service.cpp  -o ${BIN_DIR}/service.o

# Factory binaries 
${BIN_DIR}/factory_deck.o: ${INCLUDE_DIR}/factories/DeckFactory.hpp ${SRC_DIR}/factories/DeckFactory.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/factories/DeckFactory.cpp  -o ${BIN_DIR}/factory_deck.o

${BIN_DIR}/factory_game.o: ${INCLUDE_DIR}/factories/GameFactory.hpp ${SRC_DIR}/factories/GameFactory.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/factories/GameFactory.cpp  -o ${BIN_DIR}/factory_game.o

${BIN_DIR}/factory_player.o: ${INCLUDE_DIR}/factories/PlayerFactory.hpp ${SRC_DIR}/factories/PlayerFactory.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/factories/PlayerFactory.cpp  -o ${BIN_DIR}/factory_player.o

# Serializers binaries
${BIN_DIR}/serializer_player.o: ${INCLUDE_DIR}/serializers/PlayerSerializer.hpp ${SRC_DIR}/serializers/PlayerSerializer.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/serializers/PlayerSerializer.cpp  -o ${BIN_DIR}/serializer_player.o

${BIN_DIR}/serializer_deck.o: ${INCLUDE_DIR}/serializers/DeckSerializer.hpp ${SRC_DIR}/serializers/DeckSerializer.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/serializers/DeckSerializer.cpp  -o ${BIN_DIR}/serializer_deck.o

${BIN_DIR}/serializer_game.o: ${INCLUDE_DIR}/serializers/GameSerializer.hpp ${SRC_DIR}/serializers/GameSerializer.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/serializers/GameSerializer.cpp  -o ${BIN_DIR}/serializer_game.o

# Data storage
${BIN_DIR}/storage.o: ${INCLUDE_DIR}/storages/Storage.hpp ${SRC_DIR}/storages/Storage.cpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/storages/Storage.cpp  -o ${BIN_DIR}/storage.o

run:
	${TARGET}

clean:
	rm -f ${BIN_DIR}/*.o ${TARGET}
