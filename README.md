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

The following badger indicates that the endpoint requires authentication: 

![Need access token in header.](https://img.shields.io/badge/Need%20access%20token%20in%20header-red)

To authenticate, see the endpoint [`POST /auth/login`](#post-authlogin) or the [Usage examples](#usage-examples) section.

### Auth Service

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

![Need access token in header.](https://img.shields.io/badge/Need%20access%20token%20in%20header-red)

It is used to log out a user.

To log out a user, just make a request to this endpoint with the token of the user in the `Authorization` header.

##### Responses

- `200 OK`: The user was successfully logged out.
- `401 Unauthorized`: The token is invalid.

### Deck Service

Endpoints for creating and managing decks.

#### `POST /decks`

![Need access token in header.](https://img.shields.io/badge/Need%20access%20token%20in%20header-red)

It is used to create a new deck.

It is not necessary to pass any data in the request body.

##### Responses

- `201 Created`: The deck was successfully created. The response body is a JSON object with the following fields:
  - `id`: The ID of the deck.
- `401 Unauthorized`: The token is invalid.

#### `GET /decks`

![Need access token in header.](https://img.shields.io/badge/Need%20access%20token%20in%20header-red)

It is used to get all the decks.

##### Responses

- `200 OK`: The decks were successfully retrieved. The response body is a JSON array with the following fields:
  - `id`: The ID of the deck.
  - `cards`: The cards of the deck.
- `401 Unauthorized`: The token is invalid.

#### `GET /decks/<deck_id>`

![Need access token in header.](https://img.shields.io/badge/Need%20access%20token%20in%20header-red)

It is used to get a deck.

##### Responses

- `200 OK`: The deck was successfully retrieved. The response body is a JSON object with the following fields:
  - `id`: The ID of the deck.
  - `cards`: The cards of the deck.
- `401 Unauthorized`: The token is invalid.
- `404 Not Found`: The deck does not exist.

#### `PUT /decks/<deck_id>`

![Need access token in header.](https://img.shields.io/badge/Need%20access%20token%20in%20header-red)

It is not possible to update a deck. This endpoint is just a placeholder.

##### Responses
- `405 Method Not Allowed`: The method is not allowed.
- `401 Unauthorized`: The token is invalid.

#### `DELETE /decks/<deck_id>`

![Need access token in header.](https://img.shields.io/badge/Need%20access%20token%20in%20header-red)

It is not possible to delete a deck. This endpoint is just a placeholder.

##### Responses

- `405 Method Not Allowed`: The method is not allowed.
- `401 Unauthorized`: The token is invalid.

### Player Service

### Game Service

## How this project is organized

## Usage examples
