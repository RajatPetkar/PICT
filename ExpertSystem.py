import time

class MedicalExpertSystem:
    def __init__(self):
        self.rules = [
            {
                "if_all": ["high_fever", "cough", "tired"],
                "conclusion": "FLU",
                "action": "Take rest, drink fluids, consult doctor."
            },
            {
                "if_all": ["high_fever", "body_pain"],
                "conclusion": "INFECTION",
                "action": "Visit doctor and take medicines."
            },
            {
                "if_all": ["cough", "cold"],
                "conclusion": "COMMON COLD",
                "action": "Take steam and drink warm water."
            },
            {
                "if_all": ["tired", "body_pain"],
                "conclusion": "FATIGUE",
                "action": "Take rest and proper diet."
            },
            {
                "if_all": ["high_fever"],
                "conclusion": "MILD FEVER",
                "action": "Take paracetamol and rest."
            }
        ]
        self.facts = {}

    def ask(self, question):
        return input(f"{question} (y/n): ").lower() == 'y'

    def gather_facts(self):
        print("="*65)
        print("     EXPERT SYSTEM: MEDICAL DIAGNOSIS     ")
        print("="*65)

        name = input("Patient Name: ")

        # Ask questions
        fever = self.ask("1. Do you have high fever?")
        cough = self.ask("2. Do you have cough?")
        pain = self.ask("3. Do you have body pain?")
        cold = self.ask("4. Do you have cold/runny nose?")
        tired = self.ask("5. Do you feel tired or weak?")

        # Store facts
        self.facts["high_fever"] = fever
        self.facts["cough"] = cough
        self.facts["body_pain"] = pain
        self.facts["cold"] = cold
        self.facts["tired"] = tired

        return name

    def inference_engine(self):
        print("\n[Inference Engine]: Checking symptoms...")
        time.sleep(1.5)

        for rule in self.rules:
            match = True

            for cond in rule["if_all"]:
                if self.facts.get(cond, False) == False:
                    match = False
                    break

            if match:
                return rule

        return {
            "conclusion": "NO MAJOR ISSUE",
            "action": "You are healthy. Maintain good lifestyle."
        }

    def run(self):
        name = self.gather_facts()
        result = self.inference_engine()

        print("\n" + "="*65)
        print(f" FINAL MEDICAL RESULT: {name.upper()} ")
        print("="*65)
        print(f"CONCLUSION : {result['conclusion']}")
        print(f"ACTION     : {result['action']}")
        print("="*65)


if __name__ == "__main__":
    MedicalExpertSystem().run()