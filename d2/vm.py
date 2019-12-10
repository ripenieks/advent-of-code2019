import sys

class VM:
    def __init__(self, rom):
        self.rom = rom
        self.IP = 0
        self.res = 0

    def step(self):
        cur_ins = int(self.rom[self.IP])

        fn = VM.OPS.get(cur_ins, None)
        print("curins", cur_ins)
        if fn is None:
            raise RuntimeError("Unknown instruction '{}' at {}".format(
                repr(cur_ins), self.IP - 1))
        else:
            res = fn(self)
        if res == -1:
            return -1
        self.IP += 4

    def add(self):
        print("add")

        r1 = self.rom[self.IP+1]
        r2 = self.rom[self.IP+2]
        out = self.rom[self.IP+3]

        self.rom[out] = self.rom[r1] + self.rom[r2]
        return 0

    def multiply(self):
        print("mult")

        r1 = self.rom[self.IP+1]
        r2 = self.rom[self.IP+2]
        out = self.rom[self.IP+3]

        self.rom[out] = self.rom[r1] * self.rom[r2]
        return 0

    def exit(self):
        print("exit")
        print("final ROM: ", self.rom)
        self.res = self.rom[0]
        return -1

    OPS = { 1:add,
            2:multiply,
            99:exit}

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("missing program")
        raise SystemExit()

    with open(sys.argv[1], "r") as f:
        print("running")
        all_ins = ['']
        all_ins.extend(f.read().split(","))
        del all_ins[0]
        all_ins = [int(i) for i in all_ins]
        orig = all_ins.copy()
        print(orig)


        for noun in range(100):
            for verb in range(100):
                all_ins[1] = noun
                all_ins[2] = verb
                vm = VM(all_ins)
                while 1:
                    if vm.step() == -1:
                        if vm.res == 19690720:
                            print(vm.rom)
                            sys.exit()
                        break
                print("BREWAK")
                all_ins = orig.copy()
                print("allins", all_ins)
                print("orig", orig)
        
