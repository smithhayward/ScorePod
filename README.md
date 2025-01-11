ScorePod is a simple score keeping and display device that uses an Arduino compatible microcontroller and a SSD1306 OLED display.

Currently focused on volleyball, the plan is to expand to other sports in the future.

The impetus for the project was live-streaming volleyball games and having to constantly announce the score out loud. The idea is to have the OLED display positioned in the corner of the live-stream feed.

v1.0 Features
=====================
Score tracking for two teams.
One button for each team.  Short press adds one to the score while a long press subtracts one.
One button to advance the set number.  A medium press is required to avoid accidental triggers.

Long-pressing the HOME SCORE button will reset the score to 0:0.
Long-pressing the SET button will reset the set to 1.
Currently limited to scores of 0 to 99 (I feel like only pro-basketball is one of the few places this would be an issue; this is geared more toward youth sports games)

Roadmap Ideas
======================
Winner detection using hard-coded score limits and win-by-2 logic.
Tracking of set and game winners hard-coded to best-of-3 games.
Setup routine at boot time for key game rules and point limits (i.e. 25 points per game; 15 points in last set; 3 sets per game, etc.)
Auto-reset to next set if game not yet won (sets one and two when both sets not won by the same team)
Special button for fun animations (Aces, Blocks, Kills for VB; Home Run, Strikeout for Baseball, etc)
Counting special events like Aces and Strikeouts.
Box Score Display
Other stat tracking and display.
Sound Effects
Additional Remote Scoreboards (for when the crowd can't see the scoreboard which is all-to-often)
Bluetooth Interactivity with existing app interfaces
Wifi Interactivity (remote view via web UI; remote control via web UI)
