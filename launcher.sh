#!/usr/bin/env bash

SOURCE=$(pacmd list-sources | grep -oP 'name: <.*monitor>' | head -n 1 | cut -d '<' -f2 | cut -d '>' -f1)

AUDIO_MONITOR_SOURCE="$SOURCE" ./audio_visualizer
