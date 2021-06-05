import subprocess

EXEC_FILE = "union-find.exe"

forum_names = ["gaming", "chess", "bioinformatics"]

if __name__ == "__main__":
    for f_name in forum_names:
        subprocess.run(
            [
                EXEC_FILE,
                f"../data/wyniki/Edges-{f_name}.csv",
                f"../data/wyniki/Vertices-{f_name}.csv",
                f"../data/wyniki/Communities-{f_name}.csv"
            ]
        )
  