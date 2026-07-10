# Kwic

Kwic is a tool that means you never have to find your API keys again. Just save it once under a name, and retrieve it whenever you need. Of course, this doesn't have to be for API keys, use it to store whatever text you need.<br>

> *I don't really know to do the fancy MD stuff you always see, so forgive the poor appearance.*

> **Important:** if you don't want to read the whole thing, please just take a look at [this](#disclaimer) and especially **[this](#dependencies)**

<br>

## How To Use

Kwic was made quite simple. It only has four commands total:

- Register a key <code>kwic -n my-api-key thisismyapikey</code>

- Copy a key to clipboard <code>kwic -c my-api-key</code>

- List all saved keys <code>kwic ls</code>

    This will return something that looks like this:

    <code>my-api-key:thisismyapikey<br>
    github-token:ghp_whatevermytokenis<br>
    stackpassword:mystackoverflowpassword</code>

    The colon simply acts as a separator between the name you set, and the value.

- Delete a key

    <code>kwic -r my-api-key</code>
    <br>or<br>
    <code>kwic rm my-api-key</code>

## Disclaimer

I've only been coding C for a month now, and this is the first project I've built in it. I know the code probably won't be up to your standards, so please feel free to make a pull request and help me out. This is the first time I've worked with a low level language due to being in secondary school.

Feel free to expand this and make any pull requests to help improve.

## dependencies

Kwic only work on **Linux systems** with **Wayland**. I will expand compatability in the future.
<br><br><br>


<footer>Thanks for using Kwic :D</footer>