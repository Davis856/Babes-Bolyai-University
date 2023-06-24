package model.statement;

import exception.ADTException;
import exception.ExpressionEvaluationException;
import exception.StatementExecutionException;
import model.programState.ProgramState;
import model.type.Type;
import model.utils.MyIDictionary;

public interface IStatement {
    ProgramState execute(ProgramState state) throws StatementExecutionException, ExpressionEvaluationException, ADTException;
    MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws StatementExecutionException, ExpressionEvaluationException, ADTException;
    IStatement deepCopy();
}
