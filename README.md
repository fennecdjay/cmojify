# Cmojify

![Cmojify in action](/img/example.png)

## What is it?

Cmojify started as a challenge fennecdjay did to create a textual API for emojis in under 10 minutes.

After some improvements, it is now a library that allows you to transform any "cmoji" string into a processed one suitable for printing and other purposes.

## How do I use it?

The API is a singular function, `cmojify`. This takes 3 parameters: an output buffer, its length, and the input "cmoji" string.

The first two parameters can be passed with:
```c
char output_buffer[whatever length];
cmojify(output_buffer, sizeof(output_buffer), __);
```

The last parameter is just the cmoji source string.

```c
char output_buffer[whatever length];
cmojify(output_buffer, sizeof(output_buffer), "Cmojify is :star:!");
```

## What's a "cmoji" string?

The strings given to the `cmojify` function are normal C strings, but they have a special syntax. If an emoji is named between two `:` then it is replaced with that emoji. In the example above, `:art:` is replaced with `🎨`.

You can escape `:` using a backslash (two backslashes in a C string), and you can escape backslashes with another backslash (four backslashes in a C string).

## Using Cmojify in your own project

### Using Cmojify as a stand-alone library

To use Cmojify as a static library, simply run:
```sh
git clone https://github.com/fennecdjay/cmojify
cd cmojify
make
```
This will build the library `libcmojify.a`.

### Using Cmojify in an existing project

To add Cmojify to an existing project, make use of git submodules:

```sh
git submodule add https://github.com/fennecdjay/cmojify
```
