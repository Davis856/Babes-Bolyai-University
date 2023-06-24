class UndoService:
    def __init__(self):
        # History of operations for undo/redo
        self._history = []
        # Our current position in undo/redo
        self._index = -1
        # Setting this to false stops recording operations for undo/redo
        self._record_flag = True

    def flag_setter(self):
        if self._record_flag:
            self._record_flag = False
            return self._record_flag
        elif not self._record_flag:
            self._record_flag = True
            return self._record_flag

    def record_operation(self, operation):
        if self._record_flag is False:
            return

        while self._index + 1 < len(self._history):
            self._history.pop()

        self._history.append(operation)
        self._index += 1

    def undo(self):
        if len(self._history) == 0:
            raise UndoException("No more things to undo!")
        self._record_flag = False
        self._history[self._index].undo()
        self._index -= 1
        self._record_flag = True

    def redo(self):
        if self._index >= len(self._history) - 1:
            raise UndoException("No existing operations to be redone.")

        self._record_flag = False
        self._history[self._index + 1].redo()
        self._index += 1
        self._record_flag = True


class UndoException(Exception):
    pass


class Operation:
    def __init__(self, function_undo, function_redo):
        self._function_undo = function_undo
        self._function_redo = function_redo

    def undo(self):
        self._function_undo.call()

    def redo(self):
        self._function_redo.call()


class CascadedOperation(Operation):
    def __init__(self):
        self._operations = []

    def add(self, operation):
        self._operations.append(operation)

    def undo(self):
        for oper in self._operations:
            oper.undo()

    def redo(self):
        for oper in self._operations:
            oper.redo()


class FunctionCall:
    def __init__(self, function_name, *function_params):
        self._function_name = function_name
        self._function_params = function_params

    def call(self):
        self._function_name(*self._function_params)
