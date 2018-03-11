class CuRRenT(object):

    template1 = '''
<!DOCTYPE html>
<!--[if lt IE 7]> <html class="no-js lt-ie9 lt-ie8 lt-ie7" lang="en"> <![endif]-->
<!--[if IE 7]>    <html class="no-js lt-ie9 lt-ie8" lang="en"> <![endif]-->
<!--[if IE 8]>    <html class="no-js lt-ie9" lang="en"> <![endif]-->
<!--[if gt IE 8]><!--> <html class="no-js" lang="en"> <!--<![endif]-->
<head>
    <title><!-- whoami --></title>
    <link rel="shortcut icon" href="<!-- dotz -->img/templates-images/icon.ico" />
    <meta charset="<!-- charset -->">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="canonical" href="<!-- addr -->">
    <meta name="author" content="<!-- author -->">
    <meta name="description" content="<!-- description -->">
    <link rel="stylesheet" href="<!-- dotz -->css/template-1/style.css">
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
                </ul>
                <div id="combo-holder"></div>
            </nav>
        </header>
            <div id="main" class="cf">
                <div id="posts-list" class="cf">
<!-- split_here -->
        <!-- pagi_or_comment -->
           </div>
            <!-- tags_bar -->
            <!-- recent_bar -->
            <!-- github_sidebar -->         
           </div>
        <footer>
            <div id="twitter-holder">
                <div class="ribbon-left"></div>
                <div class="ribbon">
                    <div id="tweets-bar" class="tweet"></div>
                </div>
                <div class="ribbon-right"></div>
            </div>
            <div id="bottom">
                <!-- footer_text -->
            </div>
        </footer>
    </div>
<!-- github_script -->
</body>
</html>
'''

    template2 = '''
<!DOCTYPE html>
<!--[if lt IE 7]>      <html class="no-js lt-ie9 lt-ie8 lt-ie7"> <![endif]-->
<!--[if IE 7]>         <html class="no-js lt-ie9 lt-ie8"> <![endif]-->
<!--[if IE 8]>         <html class="no-js lt-ie9"> <![endif]-->
<!--[if gt IE 8]><!--> <html class="no-js"> <!--<![endif]-->
    <head>
        <link rel="shortcut icon" href="<!-- dotz -->img/templates-images/icon.ico" />
        <meta charset="<!-- charset -->">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="canonical" href="<!-- addr -->">
        <meta name="author" content="<!-- author -->">
        <meta name="description" content="<!-- description -->">
        <title><!-- whoami --></title>
        <meta name="viewport" content="width=device-width">
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
                </ul>
            </nav>
            <div id="main" class="cf">
                <div id="posts-list" class="cf">
<!-- split_here -->
    <!-- pagi_or_comment -->
        </div>
        <!-- tags_bar -->
        <!-- recent_bar -->
        <!-- github_sidebar -->
            </div>
            <div class="footer-divider"></div>
            <footer class="cf">
                <!-- footer_text -->
            </footer>
        </div>
        <!-- github_script -->
    </body>
</html>
'''

    template3 = '''
<!DOCTYPE html>
<html lang="en">
    <head>
        <link rel="shortcut icon" href="<!-- dotz -->img/templates-images/icon.ico" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="canonical" href="<!-- addr -->">
        <meta charset="<!-- charset -->">
        <meta name="author" content="<!-- author -->">
        <meta name="description" content="<!-- description -->">
        <title><!-- whoami --></title>
        <link rel="stylesheet" id="elegantwhite_style-css" href="<!-- dotz -->css/template-3/style.css" type="text/css" media="all">
    </head>
<body class="home blog">
<div id="line"></div>
<div id="container">
<div id="blogtitle"><a class="heading" href="<!-- dotz -->index.html"><!-- title --></a></div>
 <div class="blogdescription"><!-- description --></div>
<div id="nav-container">
    <div id="nav"><div class="menu">
    <div class="nav"><ul><li><a href="<!-- dotz -->index.html">Home</a></li><li><a href="<!-- dotz -->archive.html">Archive</a></li>
        </ul></div>
</div></div></div>
  <div id="header-settings">
<div id="second-container">
</div>
<div id="kontent">
    <hr>
<!-- split_here -->
<!-- pagi_or_comment -->
</div> 
    <!-- tags_bar -->
    <!-- recent_bar -->
    <!-- github_sidebar -->
    <div id="clear"></div>
</div>
<div class="line-footer">
    <div style="text-align:center; padding-top:10px;">
        <!-- footer_text -->
    </div>
   </div>
  </div>    
</div>
<!-- github_script -->
</body></html>
'''