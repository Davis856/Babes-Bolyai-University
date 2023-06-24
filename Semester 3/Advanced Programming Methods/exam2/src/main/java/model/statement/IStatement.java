package model.statement;

import exception.InterpreterException;
import model.programState.ProgramState;
import model.type.Type;
import model.utils.MyIDictionary;

public interface IStatement {
    ProgramState execute(ProgramState state) throws InterpreterException;
    MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException;
    IStatement deepCopy();
}