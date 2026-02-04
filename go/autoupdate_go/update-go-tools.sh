#!/bin/bash
# ./go/autoupdate_go/update-go-tools.sh
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Locate go-tools.txt
if [[ -f "$SCRIPT_DIR/go-tools.txt" ]]; then
  TOOLS_FILE="$SCRIPT_DIR/go-tools.txt"
elif [[ -f "./go-tools.txt" ]]; then
  TOOLS_FILE="./go-tools.txt"
else
  echo "❌ Error: go-tools.txt not found in script directory or current working directory."
  exit 1
fi

GO_BIN_DIR="$(go env GOPATH)/bin"

echo "📦 Updating Go tools into: $GO_BIN_DIR"
echo "📝 Using list from: $TOOLS_FILE"
echo

while IFS= read -r line; do
  tool=$(echo "$line" | sed 's/#.*//' | xargs)
  [ -z "$tool" ] && continue

  tool_name=$(basename "$(echo "$tool" | cut -d@ -f1)")
  bin_path="$GO_BIN_DIR/$tool_name"

  mod_before=0
  [[ -f "$bin_path" ]] && mod_before=$(stat -c %Y "$bin_path")

  echo "🔧 Installing: $tool"
  go install "$tool"

  mod_after=$(stat -c %Y "$bin_path" 2>/dev/null || echo 0)

  if [[ "$mod_after" -gt "$mod_before" ]]; then
    echo "✅ Updated: $tool_name"
  else
    echo "⏭️  Already up-to-date: $tool_name"
  fi
  echo
done < "$TOOLS_FILE"

echo "✅ $TOOLS_FILE list finished."
echo

# Install golangci-lint
# Different installation method: https://golangci-lint.run/docs/welcome/install/#local-installation
echo "🔧 Installing: golangci-lint"
curl -sSfL https://raw.githubusercontent.com/golangci/golangci-lint/master/install.sh | sh -s -- -b "$(go env GOPATH)/bin"
echo "✅ golangci-lint installed"
echo

echo "🎉 All tools processed."
