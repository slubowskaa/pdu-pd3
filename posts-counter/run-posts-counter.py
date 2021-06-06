import subprocess

EXEC_FILE = "PostsCounter.exe"

forum_names =  [
    "gaming",
    "chess",
    "bioinformatics",
    "health",
    "beer",
    "bicycles",
    "coffee",
    "fitness",
    "lifehacks",
    "music",
    "photo",
    "travel",
    "vegetarianism",
    "pets",
    "parenting",
    "cooking",
    "bitcoin",
    "astronomy",
    "literature",
    "sports"
]

if __name__ == "__main__":
    for f_name in forum_names:
        subprocess.run(
            [
                EXEC_FILE,
                f"../data/wyniki/PostsForCounting-{f_name}.csv",
                f"../data/wyniki/Vertices-{f_name}.csv",
                f"../data/wyniki/UsersPostsCount-{f_name}.csv"
            ]
        )
