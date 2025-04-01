import os
import subprocess
from datetime import datetime

EXECUTABLE = os.path.abspath("./src/output/app")
CONFIG_FILE = os.path.abspath("./configs/c2.txt")

def run_benchmark():
    print("⏳ Running benchmark...")
    results = []

    for _ in range(3):
        result = subprocess.run(
            ["/usr/bin/time", "-p", EXECUTABLE, CONFIG_FILE],
            stderr=subprocess.PIPE, stdout=subprocess.DEVNULL, text=True
        )

        output = result.stderr.strip()
        print(f"Raw time output:\n{output}\n")  # Debugging

        # Extract times (now with three decimals)
        times = {}
        for line in output.split("\n"):
            try:
                key, value = line.split()
                times[key] = float(value)
            except ValueError:
                print(f"Skipping malformed line: {line}")  # Debugging malformed lines

        results.append(times)

    return results

def write_results(results):
    now = datetime.now().strftime("%d-%m-%Y - %H:%M")
    avg_real = sum(r["real"] for r in results) / 3
    avg_user = sum(r["user"] for r in results) / 3
    avg_sys = sum(r["sys"] for r in results) / 3

    with open("Benchmarks.md", "a") as f:
        f.write(f"\n## {now}\n")
        for r in results:
            f.write(f"\nreal\t{r['real']:.6f}s  \nuser\t{r['user']:.6f}s  \nsys\t{r['sys']:.6f}s  \n")
        f.write(f"\n**Average real** = {avg_real:.6f}s  \n")
        f.write(f"**Average user** = {avg_user:.6f}s  \n")
        f.write(f"**Average sys** = {avg_sys:.6f}s  \n")

if __name__ == "__main__":
    results = run_benchmark()
    write_results(results)
    print("✅ Benchmark results saved to Benchmarks.md")
