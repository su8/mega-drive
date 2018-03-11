
myTags = map show [1 .. 3 :: Int]

------------------------------------------------------------------------
-- Replace the tags names with icons
--
brown   = "#333333"
white   = "#FFFFFF"
blue    = "#306eff"
bluefg  = "^fg("++ blue ++")"
icondir = "^i(/home/frost/.xmonad/icons/"

myDzenPP h = defaultPP
	{ ppCurrent         = dzenColor (white) (brown) . \wsId -> dropIx wsId
	, ppVisible         = dzenColor (white) (brown) . \wsId -> dropIx wsId
	, ppHidden          = dzenColor (brown) ""      . \wsId -> dropIx wsId
	, ppHiddenNoWindows = dzenColor (brown) ""      . \wsId -> dropIx wsId
	, ppUrgent          = dzenColor (white) (brown) . \wsId -> dropIx wsId
	, ppSep             = " "
	, ppWsSep           = " "
	, ppTitle           = dzenColor ("#222222") "" -- hide window title with darker colour
	, ppLayout          = dzenColor (brown) "" .
		(\x -> case x of
		"Tall"                       -> bluefg ++ icondir ++ "ws/tile.xbm)"
		"Mirror Tall"                -> bluefg ++ icondir ++ "ws/nbstack.xbm)"
		"Grid"                       -> bluefg ++ icondir ++ "ws/grid.xbm)"
		"Spacing 5 ResizableTall"    -> bluefg ++ icondir ++ "ws/tile.xbm)"
		"Simple Float"               -> bluefg ++ icondir ++ "ws/float.xbm)"
		_ -> x
		)
	, ppOutput = hPutStrLn h
	}
	where
	dropIx wsId = replacews wsId
		where
		replacews x
			| x == "1" = icondir ++ "tags/mouse_01.xbm)"
			| x == "2" = icondir ++ "tags/half.xbm)"
			| x == "3" = icondir ++ "tags/fox.xbm)"
