package com.comert.gEmbedded.api;

public abstract class ApplicationException extends Exception {
    private final String property;

    protected ApplicationException(String message){
        super(message);
        this.property="";
    }


    protected ApplicationException(ApplicationMessage applicationMessage, String property) {
        super(applicationMessage.getMessage());
        this.property = property;
    }

    @Override
    public String getMessage() {
        return super.getMessage() + " : " + property;
    }

}
