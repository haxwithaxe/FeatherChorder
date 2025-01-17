# FeatherChorder
This is a wired and bluetooth chording keyboard. It is a modified version of [FeatherChorder]() written for the [AdaFruit Feather Bluefruit](https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/overview).

Original inspiration [Spiffchorder](http://chorder.cs.vassar.edu/).

# Parts

# Circuit

# Chords
## Left hand chords
These are the chords with the keys laid out as if the chorder is held in the left hand.
```
| Pinky | Ring | Middle | Index |- Finger keys
                                | Near | \
                                | Mid  |  |- Thumb keys
                                | Far  | /
```

## Default Mode
|Key|Shifted|Pinky|Ring|Middle|Index|Near|Mid|Far|Hint|
|----|----|----|----|----|----|----|----|----|----|
|w|W|0|-|-|-|-|-|-||
|y|Y|-|0|-|-|-|-|-||
|u|U|0|0|-|-|-|-|-||
|r|R|-|-|0|-|-|-|-||
|(||0|-|0|-|-|-|-||
|h|H|-|0|0|-|-|-|-||
|s|S|0|0|0|-|-|-|-||
|i|I|-|-|-|0|-|-|-||
|b|B|0|-|-|0|-|-|-||
|k|K|-|0|-|0|-|-|-||
|z|Z|0|0|-|0|-|-|-||
|d|D|-|-|0|0|-|-|-||
|}||0|-|0|0|-|-|-||
|e|E|-|0|0|0|-|-|-||
|t|T|0|0|0|0|-|-|-||
|MODE_NUM||-|-|-|-|0|-|-|Enter Number/Symbol mode|
|MODE_FUNC||0|-|-|-|0|-|-|Enter Function mode|
|esc||-|0|-|-|0|-|-|Escape|
|;||0|0|-|-|0|-|-||
|,||-|-|0|-|0|-|-||
|}||0|-|0|-|0|-|-||
|.||-|0|0|-|0|-|-||
|Left Alt||0|0|0|-|0|-|-||
|Insert||0|-|-|0|0|-|-||
|Left GUi||-|0|-|0|0|-|-|Windows/Command/Meta|
|Left CTRL||0|0|-|0|0|-|-|Left Control|
|F9||-|-|0|0|0|-|-||
|{||0|-|0|0|0|-|-||
|'|"|-|0|0|0|0|-|-|Quote|
|NumLock||0|0|0|0|0|-|-||
|Space||-|-|-|-|-|0|-||
|f|F|0|-|-|-|-|0|-||
|g|G|-|0|-|-|-|0|-||
|v|V|0|0|-|-|-|0|-||
|c|C|-|-|0|-|-|0|-||
|]||0|-|0|-|-|0|-||
|p|P|-|0|0|-|-|0|-||
|n|N|0|0|0|-|-|0|-||
|l|L|-|-|-|0|-|0|-||
|x|X|0|-|-|0|-|0|-||
|j|J|-|0|-|0|-|0|-||
|q|Q|0|0|-|0|-|0|-||
|m|M|-|-|0|0|-|0|-||
|[||0|-|0|0|-|0|-||
|a|A|-|0|0|0|-|0|-||
|o|O|0|0|0|0|-|0|-||
|MULTI_NumShift||-|-|-|-|0|0|-|Enter Number/Symbol mode with Shift held|
|DPAD Center||-|-|0|-|0|0|-|Android DPAD Center|
|Android Home||-|0|0|-|0|0|-|Android Home|
|Right Alt||0|0|0|-|0|0|-||
|Android Back||0|-|-|0|0|0|-|Android Back|
|Right GUI||-|0|-|0|0|0|-|Windows/Command/Meta|
|Right CTRL||0|0|-|0|0|0|-|Right Control|
|Menu||-|-|0|0|0|0|-|Android Menu|
|Search||-|0|0|0|0|0|-|Android Search|
|NumLock||0|0|0|0|0|0|-||
|Left Shift||-|-|-|-|-|-|0||
|Enter||0|-|-|-|-|-|0||
|Right||-|0|-|-|-|-|0||
|Down||0|0|-|-|-|-|0||
|Backspace||-|-|0|-|-|-|0||
|PrintScreen||0|-|0|-|-|-|0||
|Delete||-|0|0|-|-|-|0||
|PageDown||0|0|0|-|-|-|0||
|Left||-|-|-|0|-|-|0||
|End||0|-|-|0|-|-|0||
|Tab||-|0|-|0|-|-|0||
|Home||0|0|-|0|-|-|0|Regular Home|
|Up||-|-|0|0|-|-|0||
|ScrollLock||0|-|0|0|-|-|0||
|PageUp||-|0|0|0|-|-|0||
|CapsLock||0|0|0|0|-|-|0||
|Break||-|-|-|-|0|-|0||
|MODE_RESET||-|-|-|-|-|0|0||
|Numpad Enter||0|-|-|-|-|0|0||
|Numpad 6||-|0|-|-|-|0|0||
|Volume Up||0|0|-|-|-|0|0||
|Stop Playback||-|-|0|-|-|0|0||
|Numpad *||0|-|0|-|-|0|0||
|Play/Pause||-|0|0|-|-|0|0||
|Next Track||0|0|0|-|-|0|0||
|Numpad 4||-|-|-|0|-|0|0||
|Previous Track||0|-|-|0|-|0|0||
|Numpad -||-|0|-|0|-|0|0||
|Numpad 7||0|0|-|0|-|0|0||
|Volume Down||-|-|0|0|-|0|0||
|Numpad /||0|-|0|0|-|0|0||
|Previous Track||-|0|0|0|-|0|0||
|Numpad 0||0|0|0|0|-|0|0||
|MODE_MRESET||-|-|-|-|0|0|0||

## Number/Symbol Mode
|Key|Shifted|Pinky|Ring|Middle|Index|Near|Mid|Far|Hint|
|----|----|----|----|----|----|----|----|----|----|
|5|5|0|-|-|-|-|-|-||
|4|4|-|0|-|-|-|-|-||
|""||0|0|-|-|-|-|-|"" and a back arrow|
|3|3|-|-|0|-|-|-|-||
|00||-|0|0|-|-|-|-|00|
|minus||0|0|0|-|-|-|-||
|2|2|-|-|-|0|-|-|-||
|Backslash||0|-|-|0|-|-|-||
|$||-|0|-|0|-|-|-|$|
|`||0|0|-|0|-|-|-|Grave|
|/||-|-|0|0|-|-|-|Forward Slash|
|=||-|0|0|0|-|-|-|Equal|
|000||0|0|0|0|-|-|-|000|
|<Space>||-|-|-|-|0|-|-||
|MODE_FUNC||0|-|-|-|0|-|-||
|Escape||-|0|-|-|0|-|-||
|;|:|0|0|-|-|0|-|-||
|,|<|-|-|0|-|0|-|-||
|.|>|-|0|0|-|0|-|-||
|Left Alt||0|0|0|-|0|-|-||
|Insert||0|-|-|0|0|-|-||
|Left GUI||-|0|-|0|0|-|-|Windows/Command/Meta|
|Left Control||0|0|-|0|0|-|-||
|'|"|-|0|0|0|0|-|-|Quote|
|MODE_RESET||0|0|0|0|0|-|-||
|1|1|-|-|-|-|-|0|-||
|9|9|0|-|-|-|-|0|-||
|8|8|-|0|-|-|-|0|-||
|]|}|0|0|-|-|-|0|-|Right Bracket|
|7|7|-|-|0|-|-|0|-||
|]|}|0|-|0|-|-|0|-|Right Bracket|
|%||-|0|0|-|-|0|-|Percent|
|[|{|0|0|0|-|-|0|-|Left Bracket|
|6|6|-|-|-|0|-|0|-||
|&||0|-|-|0|-|0|-||
|()||-|0|-|0|-|0|-|() and a back arrow|
|?||0|0|-|0|-|0|-|Question Mark|
|*||-|-|0|0|-|0|-|Asterisk|
|[|{|0|-|0|0|-|0|-|Left Bracket|
|+||-|0|0|0|-|0|-|Plus|
|0|0|0|0|0|0|-|0|-||
|MULTI_NumShift||-|-|-|-|0|0|-|Enter Number/Symbol mode with Shift held|
|DPAD Center||-|-|0|-|0|0|-|Android DPAD Center|
|Home||-|0|0|-|0|0|-|Android Home|
|Right Alt||0|0|0|-|0|0|-||
|Back||0|-|-|0|0|0|-|Android Back|
|Right GUI||-|0|-|0|0|0|-|Windows/Command/Meta|
|Right CTRL||0|0|-|0|0|0|-|Right Control|
|Menu||-|-|0|0|0|0|-|Android Menu|
|Search||-|0|0|0|0|0|-|Android Search|
|NumLock||0|0|0|0|0|0|-||
|Left Shift||-|-|-|-|-|-|0||
|Enter||0|-|-|-|-|-|0||
|Right||-|0|-|-|-|-|0|Right Arrow|
|Down||0|0|-|-|-|-|0|Down Arrow|
|Backspace||-|-|0|-|-|-|0||
|PrintScreen||0|-|0|-|-|-|0||
|Delete||-|0|0|-|-|-|0||
|Page Down||0|0|0|-|-|-|0||
|Left||-|-|-|0|-|-|0|Left Arrow|
|End||0|-|-|0|-|-|0||
|Tab||-|0|-|0|-|-|0||
|Home||0|0|-|0|-|-|0||
|Up||-|-|0|0|-|-|0|Up Arrow|
|ScrollLock||0|-|0|0|-|-|0||
|Page Up||-|0|0|0|-|-|0||
|CapsLock||0|0|0|0|-|-|0||
|Break||-|-|-|-|0|-|0||
|MODE_RESET||-|-|-|-|-|0|0||
|Numpad Enter||0|-|-|-|-|0|0||
|Numpad 6||-|0|-|-|-|0|0||
|Numpad 2||0|0|-|-|-|0|0||
|Numpad 5||-|-|0|-|-|0|0||
|Numpad *||0|-|0|-|-|0|0||
|Numpad ,||-|0|0|-|-|0|0||
|Numpad 3||0|0|0|-|-|0|0||
|Numpad 4||-|-|-|0|-|0|0||
|Numpad 1||0|-|-|0|-|0|0||
|Numpad -||-|0|-|0|-|0|0||
|Numpad 7||0|0|-|0|-|0|0||
|Numpad 8||-|-|0|0|-|0|0||
|Numpad /||0|-|0|0|-|0|0||
|Numpad 9||-|0|0|0|-|0|0||
|Numpad 0||0|0|0|0|-|0|0||
|MODE_RESET||-|-|-|-|0|0|0||

## Function Mode
|Key|Shifted|Pinky|Ring|Middle|Index|Near|Mid|Far|Hint|
|----|----|----|----|----|----|----|----|----|----|
|F5||0|-|-|-|-|-|-||
|F4||-|0|-|-|-|-|-||
|Volume Up||0|0|-|-|-|-|-||
|F3||-|-|0|-|-|-|-||
|Stop||0|0|0|-|-|-|-|Stop playback|
|F2||-|-|-|0|-|-|-||
|Previous Track||0|-|-|0|-|-|-||
|Volume Down||-|-|0|0|-|-|-||
|MODE_RESET||0|-|-|-|0|-|-||
|Left Alt||0|0|0|-|0|-|-||
|Left GUI||-|0|-|0|0|-|-|Windows/Command/Meta|
|Left CTRL||0|0|-|0|0|-|-|Left Control|
|F1||-|-|-|-|-|0|-||
|F9||0|-|-|-|-|0|-||
|F8||-|0|-|-|-|0|-||
|F12||0|0|-|-|-|0|-||
|F7||-|-|0|-|-|0|-||
|F11||-|0|0|-|-|0|-||
|F6||-|-|-|0|-|0|-||
|F10||-|-|0|0|-|0|-||
|MULTI_NumShift||-|-|-|-|0|0|-|Enter number/symbol mode with Shift held|
|DPAD Center||-|-|0|-|0|0|-|Android DPAD Center|
|Home||-|0|0|-|0|0|-|Android Home|
|Right Alt||0|0|0|-|0|0|-||
|Back||0|-|-|0|0|0|-|Android Back|
|Right GUI||-|0|-|0|0|0|-|Windows/Command/Meta|
|Right CTRL||0|0|-|0|0|0|-|Right Control|
|Menu||-|-|0|0|0|0|-|Android Menu|
|Search||-|0|0|0|0|0|-|Android Search|
|Left Shift||-|-|-|-|-|-|0||
|Play/Pause||-|0|0|-|-|-|0||
|Next Track||0|0|0|-|-|-|0||
|Previous Track||-|-|-|0|-|-|0||
|MODE_RESET||-|-|-|-|-|0|0||
|MODE_RESET||-|-|-|-|0|0|0||
