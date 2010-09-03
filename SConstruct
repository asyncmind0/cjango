env = Environment()

target = 'cjango';

sources = [
    'CommentNode.cpp',
    'Context.cpp',
    'Filter.cpp',
    'FilterFactory.cpp',
    'Node.cpp',
    'NullTagNode.cpp',
    'Parser.cpp',
    'TagNode.cpp',
    'TagNodeFactory.cpp',
    'TemplateNode.cpp',
    'TextNode.cpp',
    'Tokenizer.cpp',
    'VariableExpression.cpp',
    'VariableNode.cpp'
    ];

env.SharedLibrary(target = target, source = sources)
env.Append(CCFLAGS = ['-g'])
env.Append(CPPPATH = ['../'])

