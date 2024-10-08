BUILD=build
PROJECT=space_invaders

init:
	cmake -B $(BUILD)

project:
	cmake --build $(BUILD)

start:
	./$(BUILD)/$(PROJECT)

clean:
	rm -rf $(BUILD)
