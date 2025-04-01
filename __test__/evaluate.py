import os
import subprocess

# Paths
EXECUTABLE = "src/output/app"
CONFIG_DIR = "./configs"
KNOWN_GOOD_DIR = "./__test__/known_solutions"
OUTPUT_FILE = "temp_output.txt"

def normalize_line(line):
    """Strips only trailing newlines but preserves tabs and internal spaces."""
    return line.rstrip("\r\n")

def compare_outputs(expected_path, actual_path):
    """Compare expected and actual output while preserving tabs."""
    with open(expected_path, "r", encoding="utf-8") as f:
        expected_lines = [normalize_line(line) for line in f.readlines()]

    with open(actual_path, "r", encoding="utf-8") as f:
        actual_lines = [normalize_line(line) for line in f.readlines()]

    if expected_lines == actual_lines:
        print("✅ Match!")
        return True

    # If mismatch, print debugging info
    print("❌ Mismatch! Debugging differences:")
    for i, (exp, act) in enumerate(zip(expected_lines, actual_lines), 1):
        if exp != act:
            print(f"🔍 Line {i}:")
            print(f"Expected: {repr(exp)}")
            print(f"Got:      {repr(act)}")

    # If one output is longer
    if len(expected_lines) != len(actual_lines):
        print(f"⚠️ Expected {len(expected_lines)} lines but got {len(actual_lines)}.")

    return False

def run_tests():
    if not os.path.exists(KNOWN_GOOD_DIR):
        print(f"❌ Error: Known good solutions directory '{KNOWN_GOOD_DIR}' not found!")
        return

    config_files = [f for f in os.listdir(CONFIG_DIR) if f.endswith(".txt")]

    if not config_files:
        print("⚠️ No config files found in the configs directory.")
        return

    for config_file in sorted(config_files):
        config_path = os.path.join(CONFIG_DIR, config_file)
        expected_output_path = os.path.join(KNOWN_GOOD_DIR, config_file)

        print(f"🔍 Testing {config_file}... ", end="")

        if not os.path.exists(expected_output_path):
            print("⚠️ Missing expected output file. Skipping.")
            continue

        # Run the program and capture output
        with open(OUTPUT_FILE, "w", encoding="utf-8") as output_file:
            result = subprocess.run([EXECUTABLE, config_path], stdout=output_file, stderr=subprocess.PIPE, text=True)

        if result.returncode != 0:
            print(f"🚨 Program crashed with error:\n{result.stderr}")
            continue

        # Compare outputs
        if compare_outputs(expected_output_path, OUTPUT_FILE):
            print("✅ Test passed!")
        else:
            print("❌ Test failed!")

    # Cleanup
    os.remove(OUTPUT_FILE)

if __name__ == "__main__":
    run_tests()
