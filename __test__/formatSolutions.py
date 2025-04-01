import os
import re

KNOWN_GOOD_DIR = "./__test__/known_solutions"

def fix_file_tabs(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        lines = f.readlines()

    fixed_lines = [re.sub(r' +', '\t', line) for line in lines]  # Replace multiple spaces with a tab

    with open(file_path, "w", encoding="utf-8") as f:
        f.writelines(fixed_lines)

    print(f"✅ Fixed: {file_path}")

def fix_all_expected_outputs():
    if not os.path.exists(KNOWN_GOOD_DIR):
        print(f"❌ Error: Expected output directory '{KNOWN_GOOD_DIR}' not found!")
        return

    files = [f for f in os.listdir(KNOWN_GOOD_DIR) if f.endswith(".txt")]

    if not files:
        print("⚠️ No expected output files found!")
        return

    for file in files:
        fix_file_tabs(os.path.join(KNOWN_GOOD_DIR, file))

    print("🎉 All expected outputs have been fixed!")

if __name__ == "__main__":
    fix_all_expected_outputs()
