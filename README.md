# Info Screen

Social media info screen for fab labs and makerspaces. Or any other place. Currently loads data from [Instagram](https://instagram.com).

![Info Screen Gif](infoScreen.gif)


## Technology

Build with [openFrameworks](http://openframeworks.cc/) and runs on the [Raspberry Pi](https://www.raspberrypi.org/). Using [ofxInstagram](https://github.com/DHaylock/ofxInstagram) by [David Haylock](https://github.com/DHaylock) and [ofxJSON](https://github.com/jefftimesten/ofxJSON) by [Jeff Crouse](https://github.com/jefftimesten).


## Setup

Please consult the readme on the [ofxInstagram](https://github.com/DHaylock/ofxInstagram) GitHub page. Before compiling on the Raspberry Pi, make sure that libcurl is installed.

```
sudo apt-get install libcurl4-openssl-dev
```

Before launching the executable, make sure that you have copied the `bin/data/config-example.xml` file to `bin/data/config.xml`. It is the place where you need to put the Instagram API access token. The contents of the file should look as follows.

```
<config>
    <access_token>your-token-here</access_token>
</config>
```

Replace the "your-token-here" part with the actual token.


## License

We use [MIT](LICENSE.md) license here. That means if you use this code, we would be happy to see the name of the [Fab Lab Berlin](http://fablab.berlin) + contributors appearing somewhere. Thanks!


## Notes

Currently the application is hardcoded to load 10 latest Instagram posts from your account. There are thoughts of making this configurable. If you have some crazy code that you believe should be added here, please submit a pull request. If the code proves usefull, you get a freebie from the Fab Lab Berlin, for example, a day where you can use any machine for free or a workshop. 