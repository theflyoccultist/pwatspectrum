#!/usr/bin/env bash

if command -v pacmd >/dev/null 2>&1; then
  SOURCE=$(pacmd list-sources | grep -oP 'name: <.*monitor>' | head -n 1 | cut -d '<' -f2 | cut -d '>' -f1)
elif command -v pactl >/dev/null 2>&1; then
  SOURCE=$(pactl list cards | grep 'device.name' | head -n 1 | cut -d '"' -f2)
else
  echo "Neither pacmd nor pactl were detected."
fi

AUDIO_MONITOR_SOURCE="$SOURCE" ./audio_visualizer
