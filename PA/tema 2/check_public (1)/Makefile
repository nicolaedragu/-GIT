# Exemplu de Makefile pentru temă.

# Numele arhivei generate de comanda `pack`, pe care o puteți trimite.
ARCHIVE := submission.zip

# Parametri pentru compilare.
CCFLAGS := -std=c++17 -Wall -Wextra -O0 -lm
JFLAGS := -Xlint:unchecked

# Directorul care conține sursele voastre, și cel unde punem binarele.
# Cel mai safe e să le lăsați așa. Dacă schimbați, folosiți path-uri relative!
SRC_DIR := .
OUT_DIR := .

# Compilăm *toate* sursele găsite în $(SRC_DIR).
# Modificați doar dacă vreți să compilați alte surse.
CC_SRC := $(wildcard $(SRC_DIR)/*.cpp)
JAVA_SRC := $(wildcard $(SRC_DIR)/*.java)

CC_EXECS := $(CC_SRC:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%)
JAVA_CLASSES := $(JAVA_SRC:$(SRC_DIR)/%.java=$(OUT_DIR)/%.class)
TARGETS := $(CC_EXECS) $(JAVA_CLASSES)


.PHONY: build clean pack

build: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OUT_DIR)/*.class $(ARCHIVE)

pack:
	@find $(SRC_DIR) \
		\( -path "./_utils/*" -prune \) -o \
		-regex ".*\.\(cpp\|h\|hpp\|java\)" -exec zip $(ARCHIVE) {} +
	@zip $(ARCHIVE) Makefile
	@[ -f README.md ] && zip $(ARCHIVE) README.md || echo "Nu uita de README.md!"
	@echo
	@echo "Am creat $(ARCHIVE)"
	@echo "Dacă vezi fișiere în plus/minus, modifică manual arhiva."
	@echo
	unzip -l $(ARCHIVE)


# Apelați soluția fiecărei probleme.
run-p1:
	$(OUT_DIR)/numarare
run-p2:
	$(OUT_DIR)/trenuri
run-p3:
	$(OUT_DIR)/drumuri
run-p4:
	$(OUT_DIR)/p4


# Reguli pentru compilare.

$(CC_EXECS): $(OUT_DIR)/%: $(SRC_DIR)/%.cpp
	g++ -o $@ $^ $(CCFLAGS)

$(JAVA_CLASSES): $(OUT_DIR)/%.class: $(SRC_DIR)/%.java
	javac $< -d $(OUT_DIR) -cp $(SRC_DIR) $(JFLAGS)
