Blogfy - Blog for you <a href="http://linux.sytes.net/" target="_blank">Demo</a>
======
Blogfy is free and open source software written in Python and designed especially for those who want to create blogs in a straightforward manner. It is the **fastest** non-compiled static website generator out there !

Blogfy got 3 custom made templates (themes), automated pagination, Atom(rss), tags, sitemap generator, user variables and advanced customizations, it is platform independent, written with performance in mind, user friendly, customizable (via **config.ini**) and fully functional, you don't have to be Einstein nor programmer neither hacker in order to start using it.

Blogfy can be faster or slower, your decisions reflect back to Blogfy's performance, either positive or negative.

## Requirements
* python2 or python3
* terminal emulator / command prompt (windows)
* any OS where python can be installed (gnu/linux,bsd,windows,macintosh,android,ios and so on...)

## Usage

Open up and modify **config.ini** according to your preferences.

To create a new 'text post' type `python2 generate.py --new 'My wonderful weekend :}'`. Want to create a new post with different author name than the one in **config.ini** ? Type: `python2 generate.py --new 'Martinez' 'Happy :)'`.
This way more than one person can create posts either on your computer or exchange them with you later, so your blog visitors will be able to see who's the post author.

Now with your favourite text editor open up the post located in **static/text posts**

To generate everything just type `python2 generate.py`
It takes exactly four steps to get started and serve your blog.

* 1. Create a new text post.
* 2. Fill the post body with text editor.
* 3. Generate everything.
* 4. Upload the 'generated' folder to your host.

The generated html files will be nested in folders. I've hosted my blog in Google drive long time ago, your host can be anyone for example: Google drive, Dropbox, Onedrive, GitHub, BitBucket and so on. In these places you can host entire blog with unlimited bandwidth and zero downtime - for free.

Let's repeat again, your host can be anyone because there are NO requirements for the host.

If your uploading speed and latency are good enough, then host the blog on your main/spare computer/server/tablet and use the python language as web server. So your blog will be generated and served only by Python. **cd** into 'generated' folder and type for
python2 web server: `python2 -m SimpleHTTPServer` or python3 web server: `python3 -m http.server`. Next, visit your domain register and point Your.External.IP:8000 , it's that simple :)

Need to replace repeating word, link or user variable in your text posts ? Type `python2 generate.py --replace 'old' 'new'`.

Let's be honest, have you ever seen static blog with more than 500 posts ? Even if you did, Blogfy will generate 500 posts (4.7 MB) with all advanced customizations set to True for 200 miliseconds, blink and you'll miss it.

Keep in mind that python2 is faster than python3. You can squeeze a little bit more speed via module optimization: `python2/3 generate.py --optimize`

### Android owners:

* Download and install <a href="https://code.google.com/p/python-for-android/downloads/detail?name=Python3ForAndroid_r6.apk&amp;can=2&amp;q=" target="_blank">Python3</a>
* Get some text editor (Quoda)
* Terminal Emulator, doesn't matter which
* ZArchiver - to unzip the Blogfy archive file

Once sl4a (python3) is downloaded, opt-in in your phone/tablet to allow application installation from unknown sources, then install the .apk file, next open up the application launcher and start the app named **Python3 For Android**, wait few seconds to check for updates, then click **Install** and wait around 2 minutes, the button 'Install' should become 'Uninstall' in case you didn't paid attention to the pop-up messages earlier. Next, download Blogfy and unzip it with ZArchiver, create new file there named **python** with some text editor and **cd** to Blogfy's dir with a terminal emulator.

The file **python** have to contain the following information as is.

```bash
#!/system/bin/sh
export EXTERNAL_STORAGE=/mnt/sdcard/com.googlecode.python3forandroid
export PY34A=/data/data/com.googlecode.python3forandroid/files/python3
export PY4A_EXTRAS=$EXTERNAL_STORAGE/extras
PYTHONPATH=$EXTERNAL_STORAGE/extras/python3
PYTHONPATH=${PYTHONPATH}:$PY34A/lib/python3.2/lib-dynload
export PYTHONPATH
export TEMP=$EXTERNAL_STORAGE/extras/python3/tmp
export HOME=/sdcard
export PYTHON_EGG_CACHE=$TEMP
export PYTHONHOME=$PY34A
export LD_LIBRARY_PATH=$PY34A/lib
$PYTHONHOME/bin/python3 "$@"
```

Now everytime when you want to create a text post or generate your blog use `sh python generate.py` or `sh python generate.py --new 'How ya doin'`, actually you can create another bash script or function to save all that typing. Bash function example:

```bash
function np {
    cd /mnt/sdcard/Download/blogfy
    sh python generate.py --new "$*"
}

# Comment #
# function usage: np How ya doin
```

If you are using GitHub to host your blog (like me), download SGit and once your local or remote repository is imported, the blog directory will be saved in **/mnt/sdcard/Android/data/me.sheimi.sgit/files**


### Useful tips:

I find it difficult to type `<p>My text goes here</p>` instead `My text goes here` on my phone and decided to include **--format** function, so you can write a text like that:

```
Unidentified.

Flying.

Sausage.
``` 

and get it formatted:

```
<p>Unidentified.</p>

<p>Flying.</p>

<p>Sausage.</p>
```

To achieve this type `python2 generate.py --format 'post_name'`, replace post_name with the real name of your post in **text posts** folder.

Question: How to include an image in my post ?

Create a user variable (if it doesn't exist) in **config.ini**, something like `$img: http://example.com/img`, then copy the image file to **generated/img** folder, and in your post type `<img src="$img/aliens.png" alt="" />`

Question: I would like to show a code in my post, but I'm not sure how you did this with the "Sausage" example above.

There you go (syntax HTML):

```
Single line code:
<pre>Unidentified Flying Sausage.</pre>

Single line code within <p> </p> text:
<p>Make it executable with <code>chmod +x file</code></p>

Multi line code with hand written <p> </p>:

<pre>

<p>Unidentified.</p>
<p>Flying.</p>
<p>Sausage.</p>

</pre>

Multi line code before --format post_name usage:

<pre>

Unidentified.
Flying.
Sausage.

</pre>
```