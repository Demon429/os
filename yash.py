import copy

class Memory():
    def __init__(self):
        self.total = 0
        self.part = 0

    def mempart(self, part):
        for i in range(len(part)):
            for key, parts in part[i].items():
                val = copy.deepcopy(parts)
                jjk1 = {}
                jjk1["name"] = key
                jjk1["capacity"] = parts
                jjk1["left"] = parts
                jjk1["occupied"] = False
                part[i] = copy.deepcopy(jjk1.copy())

    def process(self, job):
        for i in range(len(job)):
            for key, pro in job[i].items():
                jjk = dict()
                jjk["cost"] = pro
                jjk["name"] = key
                jjk["allocated"] = None
                job[i] = copy.deepcopy(jjk.copy())

    def first(self, job, part):
        for p in part:
            for j in job:
                if (p["left"] >= j["cost"]) and not j["allocated"]:
                    p["left"] -= j["cost"]
                    p["occupied"] = True
                    j["allocated"] = p["name"]

    def worst(self, job, part):
        part.sort(key=lambda x: x["capacity"], reverse=True)
        for p in part:
            for j in job:
                if (p["left"] >= j["cost"]) and not j["allocated"]:
                    p["left"] -= j["cost"]
                    p["occupied"] = True
                    j["allocated"] = p["name"]

    def best(self, job, part):
        part.sort(key=lambda x: x["capacity"])
        for p in part:
            for j in job:
                if (p["left"] >= j["cost"]) and not j["allocated"]:
                    p["left"] -= j["cost"]
                    p["occupied"] = True
                    j["allocated"] = p["name"]

    def allocEff(self, part):
        eff, left = 0, 0
        for p in part:
            eff += p["left"] / p["capacity"]
            left += p["left"]
        jjk = {"Efficiency": eff, "Leftover": left}
        return jjk

def switch(i, part, mem, job):
    if i == 0:
        mem.first(job, part)
    elif i == 1:
        mem.worst(job, part)
    elif i == 2:
        mem.best(job, part)
    else:
        print("You Dumb!")

part = [[{"A": 110}, {"B": 150}, {"C": 140}] for i in range(3)]
job = [[{"A": 110}, {"B": 140}, {"C": 120}] for i in range(3)]
tittle = [" First Fit", " Worst Fit", " Best Fit"]
mem = Memory()
for i in range(3):
    mem.mempart(part[i])
    mem.process(job[i])
    switch(i, part[i], mem, job[i])
    jjk = mem.allocEff(part[i])
    print(f"{tittle[i]}: \n")
    print(f" Memory Paritions: {part[i]} \n Processes: {job[i]}")
    print(" Leftover Memory: " + str(jjk["Leftover"]))
    print()