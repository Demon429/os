import copy

def fifo(ref):
    global frame, queue
    j = 0
    hit, fault = 0, 0
    for i in ref:
        if i in frame:
            hit += 1
        elif j == 3:
            frame[frame.index(queue.pop(0))] = i
            fault += 1
            queue.append(i)
        else:
            frame[j] = i
            j += 1
            fault += 1
            queue.append(i)
    print(" ", frame)
    return {"Hit": hit, "Fault": fault}

def lru(ref):
    global frame, queue
    j, hit, fault = 0, 0, 0
    for i in ref:
        if i in frame:
            hit += 1
            queue.append(queue.pop(queue.index(i)))
        elif j == 3:
            queue.append(i)
            frame[frame.index(queue.pop(0))] = i
            fault += 1
        else:
            frame[j] = i
            j += 1
            fault += 1
            queue.append(i)
    print(" ", frame)
    return {"Hit": hit, "Fault": fault}

def optimal(ref):
    global frame, queue
    j, hit, fault = 0, 0, 0
    flag = True
    for i in range(len(ref)):
        temp = copy.deepcopy(ref[i])
        ref[i] = -1
        if temp in frame:
            hit += 1
        elif j == 3:
            test = []
            for k in range(len(frame)):
                if frame[k] in ref:
                    test.append(ref.index(frame[k]))
                else:
                    frame[k] = temp
                    flag = False
                    break
            if flag:
                frame[frame.index(ref[max(test)])] = temp
                queue.append(temp)
            else:
                frame[j] = temp
                j += 1
                fault += 1
                queue.append(temp)
    print(" ", frame)
    return {"Hit": hit, "Fault": fault}

page_number = input(" Number of frames: ")
page_number = int(page_number)
ref = input(" Enter reference string: ").split(' ')
for i in range(len(ref)):
    ref[i] = int(ref[i])
queue = []
frame = [None] * page_number
choice = -1
while choice!= 4:
    choice = input("\n 1. FIFO\n 2. LRU\n 3. Optimal\n 4. Exit\n Enter your choice: ")
    choice = int(choice)
    if choice == 1:
        result = fifo(ref)
        print(" ", result)
    elif choice == 2:
        result = lru(ref)
        print(" ", result)
    elif choice == 3:
        result = optimal(ref)
        print(" ", result)
    elif choice == 4:
        print(" Exiting...")
    else:
        print(" Invalid Choice")
queue = []
frame = [None] * page_number