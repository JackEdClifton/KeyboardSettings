#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SERVICE_NAME="keyboard-settings.service"

mkdir -p "$HOME/.config/systemd/user"

echo "
[Unit]
Description=Keyboard Settings

[Service]
ExecStart=$SCRIPT_DIR/keyboard-settings
Restart=on-failure

[Install]
WantedBy=default.target
" > "$HOME/.config/systemd/user/$SERVICE_NAME"

systemctl --user daemon-reload
systemctl --user enable $SERVICE_NAME
systemctl --user start $SERVICE_NAME
