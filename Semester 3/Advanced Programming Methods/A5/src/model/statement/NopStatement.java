package model.statement;

import exception.ADTException;
import exception.ExpressionEvaluationException;
import exception.StatementExecutionException;
import model.programState.ProgramState;
import model.type.Type;
import model.utils.MyIDictionary;

public class NopStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws StatementExecutionException, ExpressionEvaluationException, ADTException {
        return typeEnv;
    }

    @Override
    public IStatement deepCopy() {
        return new NopStatement();
    }

    @Override
    public String toString() {
        return "NopStatement";
    }

}
