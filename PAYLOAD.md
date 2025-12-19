GET /
Header: 'Authorization: Bearer 123'
Header: 'X-Custom: value'
{
    "foo": "bar",
    "baz": 123
}


GET /ping
Header: 'Authorization: Bearer 123'
Header: 'X-Custom: value'
{
    "foo": "bar",
    "baz": 123
}


POST /post
Header: 'Authorization: Bearer 123'
Header: 'X-Custom: value'
{
    "foo": "bar",
    "baz": 123,
    "dict": {
        "hello" : "world"
    }
}

PUT /put
Header: 'Authorization: Bearer 123'
Header: 'X-Custom: value'
{
  "hello": "world"
}

DELETE /delete
Header: 'Authorization: Bearer 123'
Header: 'X-Custom: value'
{
    "foo": "bar",
    "baz": 123
}
