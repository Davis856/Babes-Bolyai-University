package controller;

import exception.ADTException;
import exception.ExpressionEvaluationException;
import exception.StatementExecutionException;
import model.programState.ProgramState;
import model.statement.IStatement;
import model.utils.MyIStack;
import model.value.RefValue;
import model.value.Value;
import repository.IRepository;

import java.io.IOException;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Controller {
    IRepository repository;
    boolean displayFlag = false;

    public void setDisplayFlag(boolean value) {
        this.displayFlag = value;
    }

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public List<Integer> getAddrFromSymTable(Collection<Value> symTableValues) {
        return symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {RefValue v1 = (RefValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    public List<Integer> getAddrFromHeap(Collection<Value> heapValues) {
        return heapValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {RefValue v1 = (RefValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    public Map<Integer, Value> safeGarbageCollector(List<Integer> symTableAddr, List<Integer> heapAddr, Map<Integer, Value> heap) {
        return heap.entrySet().stream()
                .filter(e -> ( symTableAddr.contains(e.getKey()) || heapAddr.contains(e.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public ProgramState oneStep(ProgramState state) throws StatementExecutionException, ADTException, ExpressionEvaluationException {
        MyIStack<IStatement> stack = state.getExeStack();
        if (stack.isEmpty())
            throw new StatementExecutionException("Program state stack is empty.");
        IStatement currentStatement = stack.pop();
        state.setExeStack(stack);
        return currentStatement.execute(state);
    }

    public void allSteps() throws ExpressionEvaluationException, ADTException, StatementExecutionException, IOException {
        ProgramState program = this.repository.getCurrentState();
        this.repository.logPrgStateExec();
        display();
        while(!program.getExeStack().isEmpty()) {
            oneStep(program);
            this.repository.logPrgStateExec();
            program.getHeap().setContent((HashMap<Integer, Value>) safeGarbageCollector(getAddrFromSymTable(program.getSymTable().getContent().values()), getAddrFromHeap(program.getHeap().getContent().values()), program.getHeap().getContent()));
            display();
        }
    }

    private void display() {
        if (displayFlag) {
            System.out.println(this.repository.getCurrentState().toString());
        }
    }
}