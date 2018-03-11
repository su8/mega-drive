import XMonad
import Control.Monad
import System.IO
import XMonad.Hooks.DynamicLog
import XMonad.Hooks.ManageDocks

import XMonad.Util.Run (spawnPipe)
import XMonad.Util.EZConfig (additionalKeys)
import XMonad.Util.SpawnOnce
import XMonad.Util.Loggers

import XMonad.Util.Themes

import XMonad.Actions.GridSelect
import XMonad.Actions.CycleWS (prevWS, nextWS)

import qualified XMonad.StackSet as W (focus, up, down)
import qualified Data.Map as M
import qualified GHC.IO.Handle.Types as H

import XMonad.Layout.Spacing
import XMonad.Layout.Fullscreen
import XMonad.Layout.NoBorders
import XMonad.Layout.ResizableTile
import XMonad.Layout.Tabbed
import XMonad.Layout.Circle
import XMonad.Layout.Cross
import XMonad.Layout.TabBarDecoration

import XMonad.Layout.PerWorkspace
import XMonad.Layout.Decoration
import XMonad.Layout.ResizeScreen
import XMonad.Layout.Simplest ( Simplest(Simplest) )

import XMonad.Prompt ( XPPosition (..) )
import XMonad.Prompt.Shell

import XMonad.ManageHook

ic = " ^i(/home/yotsuba/.xmonad/symbol/"

ruangKerja :: [String]
ruangKerja = clickable $ [ ic ++ "diskette.xbm) "
			 , ic ++ "fox.xbm) "
			 , ic ++ "half.xbm) "
			 , ic ++ "info_03.xbm) "
			 , ic ++ "mail.xbm) "
			 , ic ++ "mouse_01.xbm) "
			 , "ムービー"
			 ]
	   where clickable l = [ "^ca(1,xdotool key super+" ++ show (n) ++ ")" ++ ws ++ "^ca()" |
	   			 (i,ws) <- zip [1..] l,
				 let n = i ]

startup = do
	  spawnOnce "xsetroot -cursor_name left_ptr &"

bg = "#2d2d2d"
fg = "#ffffff"
sg = "#444444"
eg = "#b1b1b1"
gg = "#929292"
bd = "#c7c7c7"

logBar h = do
	dynamicLogWithPP $ tryPP h
tryPP :: Handle -> PP
tryPP h = defaultPP
	{ ppOutput		= hPutStrLn h
	, ppCurrent		= dzenColor fg sg . pad
	, ppVisible		= dzenColor gg fg . pad
	, ppHidden		= dzenColor sg fg . pad
	, ppHiddenNoWindows	= dzenColor bd fg . pad
	, ppWsSep		= ""
	, ppSep			= "   ^r(6x6)    "
	, ppTitle		= \t -> ""
	, ppLayout		= dzenColor sg fg . 
				  ( \t -> case t of
				    "Spacing 8 ResizableTall"		-> "  " ++ k ++ "tile.xbm)   tile 8"
				    "Spacing 5 ResizableTall"		-> "  " ++ k ++ "tile.xbm)   tile"
				    "ResizableTall"			-> "  " ++ k ++ "monocle.xbm)   mono"
				    "Tabbed Simplest"			-> "  " ++ k ++ "nbstack.xbm)   tab"
				    "Full"				-> "  " ++ k ++ "monocle2.xbm)   full"
				    "Circle"				-> "  " ++ "::   Circle"
				    "Cross"				-> "  " ++ ">>   Cross"
				  )
	}
	where k = "^i(/home/yotsuba/.xmonad/ws/"

gsconfig2 colorizer = (buildDefaultGSConfig colorizer) { gs_cellheight = 50, gs_cellwidth = 150 }

greenColorizer = colorRangeFromClassName
			black 
			(0x70,0xFF,0x70)
			black
			white
			white
   where black = minBound
   	 white = maxBound
lau = "dmenu_run -p 'start' -fn 'Meslo LG L for Powerline-14' -nb '#2d2d2d' -sb '#6b6b6b' -x 200 -y 200 -w 260"
res = "xmonad --recompile && killall dzen2 && xmonad --restart"

tombol = [ ((mod4Mask .|. shiftMask, xK_r	), spawn res)	 
	 , ((mod4Mask, xK_r			), spawn lau)
	 
	 , ((mod4Mask, xK_m			), sendMessage MirrorShrink)
	 , ((mod4Mask, xK_u			), sendMessage MirrorExpand)
	 
	 , ((mod4Mask, xK_g			), goToSelected $ gsconfig2 greenColorizer )
	 
	 , ((mod4Mask, xK_Left			), prevWS)
	 , ((mod4Mask, xK_Right 		), nextWS)
	 ]

--hook = composeAll . concat $
--	[ [ resource =? r --> doF (W.view "film" . W.shift "film") | r <- video ]
--	] <+> manageHook defaultConfig
--	where video = ["vlc", "MPlayer"]

-- tb :: ModifiedLayout (Decoration TabbedDecoration DefaultShrinker) Simplest Window
-- tb = tabbed shrinkText defaultTheme

--tabbed 	   :: (Eq a, Shrinker s) => s -> Theme
--	   -> ModifiedLayout (Decoration TabbedDecoration s) Simplest a
--tabbed s c = addTabs s c Simplest

rz = spacing 5 $ ResizableTall 2 (3/200) (7/13) []
fl = noBorders (fullscreenFull Full)
fk = noBorders $ ResizableTall 1 (1/1) (1/1) []
st = spacing 8 $ ResizableTall 1 (2/100) (1/2) []
tb = noBorders $ tabbed shrinkText (theme temaTab)
cr = avoidStruts $ Circle
sc = avoidStruts $ Cross (1/2) (1/100)

temaTab :: ThemeInfo
temaTab =
    smallClean { themeName	    = "temaTab"
               , themeAuthor	    = "Rizal M. Solichudin"
	       , themeDescription   = "tema yang kayak taek"
	       , theme	    = defaultTheme { activeColor	 = "#2d2d2d"
					   , activeBorderColor	 = "#2d2d2d"
					   , activeTextColor	 = "#ffffff"
					   , inactiveColor	 = "#444444"
					   , inactiveBorderColor = "#444444"
					   , inactiveTextColor	 = "#9c9c9c"
					   , decoHeight		 = 24
					   , decoWidth		 = 350
					   , fontName		 = "xft:Open Sans-8"
	 				   }
	     }

main = do
	panel <- spawnPipe top
	info <- spawnPipe sys
	xmonad $ defaultConfig
		{ manageHook = manageDocks <+> manageHook defaultConfig
		, layoutHook = avoidStruts (st ||| fk ||| rz ||| tb ||| cr ||| sc) ||| fl
		, modMask = mod4Mask
		, workspaces = ruangKerja
		, terminal = "urxvt"
		, focusedBorderColor = "#151515" -- "#f0f0f0" -- "#9e9e9e" -- "#ffd7d7"
		, normalBorderColor = "#151515" -- "#ffffff"
		, borderWidth = 1
		, logHook = logBar panel
		} `additionalKeys` tombol
		where top = "dzen2 -p -ta l -e 'button3=' -fn '"++nof++"' -fg '#2d2d2d' -bg '#ffffff' -h 24 -w 700"
		      sys = "sh /home/yotsuba/.xmonad/script/sysinfo.sh"
		      fon = "Sazanami Gothic,さざなみゴシック-8"
		      nof = "IPAPGothic,IPA Pゴシック-8"

