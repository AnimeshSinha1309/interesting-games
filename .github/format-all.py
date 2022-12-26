import os


excludes = [".git", ".clwb", ".vscode", ".idea", "bazel-"]
for dirpath, dirname, files in os.walk("."):
    if not any([exclude in dirpath for exclude in excludes]):
        filename: str = None
        for file in files:
            filepath = os.path.join(dirpath, file)
            if ".py" in file:
                os.system(f"python -m black {filepath}")
            if ".cpp" in file or ".hpp" in file:
                os.system(f"clang-format {filepath} --style=Google -i")
            if ".bazel" in file:
                os.system(f"buildifier {filepath}")
