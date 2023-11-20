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

### Auth Service

The auth service is a simple token-based authentication service, and is used to authenticate users.

> Except when creating a user and logging in, all the other endpoints require a token to be passed in the `Authorization` header with value `<token>`.

#### `POST /auth/login`

It is used to log in a user.

The body of the request must be a JSON object with the following fields:

- `username`: The username of the user.
- `password`: The password of the user.

#### `POST /auth/logout`

It is used to log out a user.

To log out a user, the token of the user must be passed in the `Authorization` header with value `<token>`.

### Deck Service

### Player Service

### Game Service

## How this project is organized

## Usage examples
