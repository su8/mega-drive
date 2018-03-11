class Template_1(object):
    forum = '''
<iframe id="forum_embed"
 src="javascript:void(0)"
 scrolling="no"
 frameborder="0"
 width="600"
 height="700">
</iframe>

<script type="text/javascript">
 document.getElementById("forum_embed").src =
  "https://groups.google.com/forum/embed/?place=forum/linuxsytesnet&showpopout=true&theme=default" +
  encodeURIComponent(window.location.href);
</script>
'''

    search = '''
<!DOCTYPE html>
<!--[if lt IE 7]> <html class="no-js lt-ie9 lt-ie8 lt-ie7" lang="en"> <![endif]-->
<!--[if IE 7]>    <html class="no-js lt-ie9 lt-ie8" lang="en"> <![endif]-->
<!--[if IE 8]>    <html class="no-js lt-ie9" lang="en"> <![endif]-->
<!--[if gt IE 8]><!--> <html class="no-js" lang="en"> <!--<![endif]-->
<head>
    <title><!-- whoami --></title>
    <link rel="shortcut icon" href="<!-- dotz -->img/templates-images/icon.ico" />
    <meta charset="<!-- charset -->">
    <meta name="viewport" content="width=device-width">
    <meta name="author" content="<!-- author -->">
    <meta name="description" content="<!-- description -->">
    <link rel="stylesheet" href="<!-- dotz -->css/template-1/style.css">
    <script type="text/javascript" src="http://www.google.com/cse/brand?form=searchform&#38;lang=en"></script>
    <script>
     (function() {
     var cx = '000510344615717143304:k7p5xn-2xbi';
     var gcse = document.createElement('script');
     gcse.type = 'text/javascript';
     gcse.async = true;
     gcse.src = (document.location.protocol == 'https:' ? 'https:' : 'http:') +
        '//www.google.com/cse/cse.js?cx=' + cx;
     var s = document.getElementsByTagName('script')[0];
     s.parentNode.insertBefore(gcse, s);
     })();
     </script>
</head>
<body><br />
    <div class="wrapper cf">
        <header class="cf">
         <div class="cf"></div>
            <div id="logo" class="cf">
              <a href="<!-- dotz -->index.html" ><img src="<!-- dotz -->img/templates-images/logo.png" alt="" /></a>
                <div class="blogdescription"><!-- description --></div>
                </div>
            <nav class="cf">
                <ul id="nav" class="sf-menu">
                    <li><a href="<!-- dotz -->index.html"><span>Home</span></a></li>
                    <li><a href="<!-- dotz -->archive.html"><span>Archive</span></a></li>
<!--                    <li><a href="forum.html"><span>Forum</span></a></li> -->
                </ul>
                <div id="combo-holder"></div>
            </nav>
        </header>
            <div id="main" class="cf">
                <div id="posts-list" class="cf"> 
                    <gcse:searchresults-only></gcse:searchresults-only>

'''

class Template_2(object):
    forum = '''
<iframe id="forum_embed"
 src="javascript:void(0)"
 scrolling="no"
 frameborder="0"
 width="640"
 height="700">
</iframe>

<script type="text/javascript">
 document.getElementById("forum_embed").src =
  "https://groups.google.com/forum/embed/?place=forum/linuxsytesnet&showpopout=true&theme=default" +
  encodeURIComponent(window.location.href);
</script>
'''

    search = '''
<!DOCTYPE html>
<!--[if lt IE 7]>      <html class="no-js lt-ie9 lt-ie8 lt-ie7"> <![endif]-->
<!--[if IE 7]>         <html class="no-js lt-ie9 lt-ie8"> <![endif]-->
<!--[if IE 8]>         <html class="no-js lt-ie9"> <![endif]-->
<!--[if gt IE 8]><!--> <html class="no-js"> <!--<![endif]-->
    <head>
        <link rel="shortcut icon" href="<!-- dotz -->img/templates-images/icon.ico" />
        <meta charset="<!-- charset -->">
        <meta name="viewport" content="width=device-width">
        <meta name="author" content="<!-- author -->">
        <meta name="description" content="<!-- description -->">
        <title><!-- whoami --></title>
        <meta name="viewport" content="width=device-width">
        <script type="text/javascript" src="http://www.google.com/cse/brand?form=searchform&#38;lang=en"></script>
<script>
  (function() {
    var cx = '000510344615717143304:k7p5xn-2xbi';
    var gcse = document.createElement('script');
    gcse.type = 'text/javascript';
    gcse.async = true;
    gcse.src = (document.location.protocol == 'https:' ? 'https:' : 'http:') +
        '//www.google.com/cse/cse.js?cx=' + cx;
    var s = document.getElementsByTagName('script')[0];
    s.parentNode.insertBefore(gcse, s);
  })();
</script>
        <link href='http://fonts.googleapis.com/css?family=Arvo:400' rel='stylesheet' type='text/css'>
        <link href='http://fonts.googleapis.com/css?family=Lato:400,700' rel='stylesheet' type='text/css'>
        <link rel="stylesheet" href="<!-- dotz -->css/template-2/style.css">
        <link rel="stylesheet" href="<!-- dotz -->css/template-2/responsive.css">

    </head>
    <body>
        <div class="wrapper">
            <header class="cf"><br />
                <div id="blogtitle"><a href="<!-- dotz -->index.html" class="heading2"><!-- title --></a></div>
                <div class="blogdescription"><!-- description --></div>
            </header>
            <nav class="cf">
                <ul id="nav" class="sf-menu">
                    <li><a href="<!-- dotz -->index.html">Home</a></li>
                    <li><a href="<!-- dotz -->archive.html">Archive</a></li>
<!--                    <li><a href="forum.html">Forum</a></li> -->
                     <form action="search.html" id="searchform">
                      <div>
                       <input type="hidden" name="cx" value="000510344615717143304:k7p5xn-2xbi" />
                       <input type="hidden" name="cof" value="FORID:11" />
                       <input type="hidden" name="ie" value="UTF-8" />
                       <input class="search-sidebar" type="text" placeholder="Search..." name="q" size="30" />
                      </div>
                     </form>
                </ul>
            </nav>
            <div id="main" class="cf">
                <div id="posts-list" class="cf">  
<gcse:searchresults-only></gcse:searchresults-only>

'''

class Template_3(object):
    forum = '''
<iframe id="forum_embed" src="https://groups.google.com/forum/embed/?showsearch=true&amp;showpopout=true&amp;place=forum/linuxsytesnet#!forum/linuxsytesnet" width="860" height="840" class="private-page"></iframe>
'''

    search = '''
<!DOCTYPE html>
<html dir="ltr" lang="en-US"><!--<![endif]--><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="shortcut icon" href="<!-- dotz -->img/templates-images/icon.ico" />
<meta name="viewport" content="width=device-width">
<meta charset="<!-- charset -->">
<meta name="author" content="<!-- author -->">
<meta name="description" content="<!-- description -->">
<title><!-- whoami --></title>
<link rel="stylesheet" id="elegantwhite_style-css" href="<!-- dotz -->css/template-3/style.css" type="text/css" media="all">
<script type="text/javascript" src="http://www.google.com/cse/brand?form=searchform&#38;lang=en"></script>
<script>
  (function() {
    var cx = '000510344615717143304:k7p5xn-2xbi';
    var gcse = document.createElement('script');
    gcse.type = 'text/javascript';
    gcse.async = true;
    gcse.src = (document.location.protocol == 'https:' ? 'https:' : 'http:') +
        '//www.google.com/cse/cse.js?cx=' + cx;
    var s = document.getElementsByTagName('script')[0];
    s.parentNode.insertBefore(gcse, s);
  })();
</script>
</head>
<body class="home blog">

<div id="line"></div>
<div id="container">
<div id="blogtitle"><a class="heading" href="<!-- dotz -->index.html"><!-- title --></a></div>
 <div class="blogdescription"><!-- description --></div>
<div id="nav-container">
    <div id="nav"><div class="menu">
    <div class="nav"><ul><li><a href="<!-- dotz -->index.html">Home</a></li><li><a href="<!-- dotz -->archive.html">Archive</a></li>
<!--    <li><a href="forum.html">Forum</a></li> -->
    </ul></div>
   
</div></div></div>
  <div id="header-settings">
<div id="second-container">
<form action="http://linux.sytes.net/search.html" id="searchform">
  <div>
    <input type="hidden" name="cx" value="000510344615717143304:k7p5xn-2xbi" />
    <input type="hidden" name="cof" value="FORID:11" />
    <input type="hidden" name="ie" value="UTF-8" />
    <input class="search-sidebar" type="text" placeholder="Search..." name="q" size="30" />
  </div>
</form>
</div>
<div id="kontent">
    <hr>

<gcse:searchresults-only></gcse:searchresults-only>
'''