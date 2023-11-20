# deck-of-cards

This project implements an API for card deck games.

The API is implemented in C++ and uses the [cpp-httplib](https://github.com/yhirose/cpp-httplib) and [nlohmann json](<https://github.com/nlohmann/json>) to parse and generate JSON.

Go to [Usage examples](#usage-examples) to see how to use the API.

## Prerequisites

To run the project, you need to have the following installed:

- `g++`: C++ compiler.
- `make`: Build automation tool.

## Building

To build the project, run the following command:

```bash
make
```

## Running

To run the project, run the following command:

```bash
make run
```

## Testing

### Unit tests

To run the tests, run the following command:

```bash
make test
```

### Integration tests

The integration tests are implemented in `Python3.8` and use the [requests](https://requests.readthedocs.io/en/master/) library to make HTTP requests.

To run the integration tests, go to...

```bash


```

## API

The next subsections describe the API endpoints.

The badger ![Authentication required.](https://img.shields.io/badge/Authentication%20required-red) indicates that the endpoint requires authentication.

> To authenticate, see the endpoint [`POST /auth/login`](#post-authlogin) or the [Usage examples](#usage-examples) section.

The badger ![Public endpoint.](https://img.shields.io/badge/Public%20endpoint-green) indicates that the endpoint is public.


This means that the endpoint does not require authentication.

### Auth Service

![Public endpoint.](https://img.shields.io/badge/Public%20endpoint-green)

The auth service is a simple token-based authentication service, and is used to authenticate users.

> Except when creating a user and logging in, all the other endpoints require a token to be passed in the `Authorization` header with value `<token>`.

#### `POST /auth/login`

It is used to log in a user.

The body of the request must be a JSON object with the following fields:

- `username`: The username of the user.
- `password`: The password of the user.

##### Responses

- `200 OK`: The user was successfully logged in. The response body is a JSON object with the following fields:
  - `token`: The token of the user.
- `400 Bad Request`: The request body is not a valid JSON object or it does not have the required fields.
- `401 Unauthorized`: The username or password is incorrect.

#### `POST /auth/logout`

![Authentication required.](https://img.shields.io/badge/Authentication%20required-red)

It is used to log out a user.

To log out a user, just make a request to this endpoint with the token of the user in the `Authorization` header.

##### Responses

- `200 OK`: The user was successfully logged out.
- `401 Unauthorized`: The token is invalid.

### Deck Service

Endpoints for creating and managing decks.

#### `POST /decks`

![Authentication required.](https://img.shields.io/badge/Authentication%20required-red)

It is used to create a new deck.

It is not necessary to pass any data in the request body.

##### Responses

- `201 Created`: The deck was successfully created. The response body is a JSON object with the following fields:
  - `id`: The ID of the deck.
- `401 Unauthorized`: The token is invalid.

#### `GET /decks`

![Authentication required.](https://img.shields.io/badge/Authentication%20required-red)

It is used to get all the decks.

##### Responses

- `200 OK`: The decks were successfully retrieved. The response body is a JSON array with the following fields:
  - `id`: The ID of the deck.
  - `cards`: The cards of the deck.
- `401 Unauthorized`: The token is invalid.

#### `GET /decks/<deck_id>`

![Authentication required.](https://img.shields.io/badge/Authentication%20required-red)

It is used to get a deck.

##### Responses

- `200 OK`: The deck was successfully retrieved. The response body is a JSON object with the following fields:
  - `id`: The ID of the deck.
  - `cards`: The cards of the deck.
- `401 Unauthorized`: The token is invalid.
- `404 Not Found`: The deck does not exist.

#### `PUT /decks/<deck_id>`

![Authentication required.](https://img.shields.io/badge/Authentication%20required-red)

It is not possible to update a deck. This endpoint is just a placeholder.

##### Responses
- `405 Method Not Allowed`: The method is not allowed.
- `401 Unauthorized`: The token is invalid.

#### `DELETE /decks/<deck_id>`

![Authentication required.](https://img.shields.io/badge/Authentication%20required-red)

It is not possible to delete a deck. This endpoint is just a placeholder.

##### Responses

- `405 Method Not Allowed`: The method is not allowed.
- `401 Unauthorized`: The token is invalid.

### Player Service

This service is used to create and manage players.

#### `POST /players`

![Public endpoint.](https://img.shields.io/badge/Public%20endpoint-green)

It is used to create a new player.

The body of the request must be a JSON object with the following fields:

- `username`: The username of the player. This field must be unique among all the players.
- `password`: The password of the player.
- `name`: The name of the player.

##### Responses

- `201 Created`: The player was successfully created. The response body is a JSON object with the following fields:
  - `id`: The ID of the player.
- `400 Bad Request`: The request body is not a valid JSON object or it does not have the required fields.
- `409 Conflict`: The username is already in use.

#### `GET /players`

![Authentication required.](https://img.shields.io/badge/Authentication%20required-red)

It is used to get all the players.

##### Responses

- `200 OK`: The players were successfully retrieved. The response body is a JSON array with the following fields:
  - `id`: The ID of the player.
  - `username`: The username of the player.
  - `name`: The name of the player.
  - `cards`: The cards of the player, if the player is in a game.
  - `playing_game`: Whether the player is playing a game, it is the ID of the game if the player is playing a game, or `null` if the player is not playing a game.
- `401 Unauthorized`: The token is invalid.

#### `GET /players/<player_id>`

![Authentication required.](https://img.shields.io/badge/Authentication%20required-red)

It is used to get a player.

##### Responses

- `200 OK`: The player was successfully retrieved. The response body is a JSON object with the following fields:
  - `id`: The ID of the player.
  - `username`: The username of the player.
  - `name`: The name of the player.
  - `cards`: The cards of the player, if the player is in a game.
  - `playing_game`: Whether the player is playing a game, it is the ID of the game if the player is playing a game, or `null` if the player is not playing a game.
- `401 Unauthorized`: The token is invalid.
- `404 Not Found`: The player does not exist.

#### `PUT /players/<player_id>`

![Authentication required.](https://img.shields.io/badge/Authentication%20required-red)

Allows update the `name` of a player and its `password`.

The body of the request must be a JSON object with the following fields:

- `name`: The new name of the player.
- `password`: The new password of the player.

It is not necessary to pass both fields in the request body, but at least one of them must be passed.

##### Responses

- `200 OK`: The player was successfully updated.
- `400 Bad Request`: The request body is not a valid JSON object or it does not have the required fields.
- `401 Unauthorized`: The token is invalid.
- `404 Not Found`: The player does not exist.

#### `DELETE /players/<player_id>`

![Authentication required.](https://img.shields.io/badge/Authentication%20required-red)

This endpoint deletes a player.

##### Responses

- `200 OK`: The player was successfully deleted.
- `401 Unauthorized`: The token is invalid.
- `404 Not Found`: The player does not exist.

### Game Service

This service is used to create and manage games.

The badger ![Only creator can access.](https://img.shields.io/badge/Only%20creator%20can%20access-yellow) indicates that only the creator of the game can access the endpoint.

#### `POST /games`

![Authentication required.](https://img.shields.io/badge/Authentication%20required-red)

It is used to create a new game.

The body of the request must be a JSON object with the following fields:
- `access_code`: The access code of the game, used to join the game.

##### Responses

- `201 Created`: The game was successfully created. The response body is a JSON object with the following fields:
  - `id`: The ID of the game.
- `400 Bad Request`: The request body is not a valid JSON object or it does not have the required fields.
- `401 Unauthorized`: The token is invalid.

#### `GET /games`

![Authentication required.](https://img.shields.io/badge/Authentication%20required-red)

It is used to get all the games.

##### Responses

- `200 OK`: The games were successfully retrieved. The response body is a JSON array with the following fields:
  - `id`: The ID of the game.
  - `creator`: The ID of the player that created the game.
  - `cards`: The cards of the game.
  - `num_decks`: The number of decks of the game.
  - `num_remaining_cards`: The number of remaining cards of the game.
  - `players`: The ids of the players of the game.
-

## How this project is organized

## Usage examples
